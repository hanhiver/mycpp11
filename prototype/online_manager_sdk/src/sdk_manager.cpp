
#include <iostream> 
#include <iomanip>
#include <unordered_map>
#include <mutex> 
#include <atomic> 
#include <thread> 
#include <ctime> 
#include <exception>

#include <curl/curl.h>
#include <glog/logging.h>

#include "timer.hpp"
#include "params.hpp"
#include "json.hpp"
#include "base64.hpp"
#include "COpenSSL.hpp"

#include "sdk_manager.hpp"

//namespace SDKManager
//{

// 服务器沟通的回调函数，负责将服务器返回的数据写入std::string
size_t OnWriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
    std::string* str = dynamic_cast<std::string*>((std::string *)lpVoid);
    if( NULL == str || NULL == buffer )
    {
        return -1;
    }
 
    char* pData = (char*)buffer;
    str->append(pData, size * nmemb);
    return nmemb;
}
// SDKManager内部的封装类，起到SDK向外接口隐藏的作用。
class SDKManager::SDKManagerImpl
{
public:
    AUTH_CODE Init(const std::string& config_file_path);
    void ConnectServer();
    void HouseKeeping();

    bool GetAuthStatus();
    void SetAuthStatus(bool status);
    void CountUsage(const std::string func_name, unsigned int call_count = 1);
    void ResetCountdown(unsigned int countdown_tick);

    std::string GenReport();
    int PostServer(const std::string& report, std::string& return_msg);
    int HandleResponse(const std::string& response, const std::string& orig_report);
    void AuthExtend(unsigned int new_countdown);
    void AuthFailed();

    void Shutdown(); 

    // 内部定时器
    Timer timer; 
    // 从配置文件中读取经过验证的公钥
    std::string mPubKey;
    // 函数调用次数记录表读写锁，应用场景中存在大量的写和少量的读取，所以暂时不用读写锁优化。
    std::mutex mRecordMutex; 
    // 函数调用次数记录表
    std::unordered_map<std::string, unsigned int> mCallRecord;
    // 向服务器汇报时候的记录表快照
    std::unordered_map<std::string, unsigned int> mSnapshot;
    // 获取鉴权失败后的重试次数
    unsigned int mRetryTime;
    // 联系服务器倒计时计数（默认单位秒）
    std::atomic<unsigned int> mCountDown;
    // 当前鉴权获取状态
    std::atomic<bool> mAuthValid;
    // 模块启动flag，控制联系服务器具体动作是否实施
    std::atomic<bool> mStarted;
};

// 获取全局SDKManager的单例实例
SDKManager& SDKManager::Get()
{
    static SDKManager instance;
    return instance;
}

// SDKManager初始化操作
AUTH_CODE SDKManager::Init(const std::string& config_filepath)
{
    LOG(INFO) << "SDK Initialize, configure file: " << config_filepath;
    AUTH_CODE res = mImpl->Init(config_filepath);

    return res; 
}

// 客户SDK调用查询鉴权状态
bool SDKManager::Auth()
{
    if (true == mImpl->GetAuthStatus())
    {
        DLOG(INFO) << "SDK got authentication successfully. "; 
        return true;
    }
    else
    {
        LOG(INFO) << "SDK failed to got authentication. ";
        return false;
    }
}

// 客户SDK调用记录函数调用次数
void SDKManager::Count(const std::string func_name, unsigned int call_count)
{
    DLOG(INFO) << "Count func_name: " << func_name << ", call_count: " << call_count;
    mImpl->CountUsage(func_name, call_count);
}

// 客户SDK调用关闭SDKManager
void SDKManager::Shutdown()
{
    LOG(WARNING) << "SDK manager shutdown. "; 
    mImpl->Shutdown();
}

SDKManager::SDKManager()
{
    DLOG(INFO) << "SDKManager() entered."; 
    // glog全局初始化。
    google::InitGoogleLogging("sdk_manager"); 
    // 是否将日志输出到stderr而非文件。
    FLAGS_logtostderr = Params::Get().GetInternalDebugOptions().log_redirect_sterr(); 
    //是否将日志输出到文件和stderr，如果：true，忽略FLAGS_stderrthreshold的限制，所有信息打印到终端。
    FLAGS_alsologtostderr = Params::Get().GetInternalDebugOptions().log_redirect_sterr();
    //设置可以缓冲日志的最大秒数，0指实时输出。 
    FLAGS_logbufsecs = 0; 
    //设置最大日志文件大小（以MB为单位）。
    FLAGS_max_log_size = 100; 
    //设置是否在磁盘已满时避免日志记录到磁盘。
    FLAGS_stop_logging_if_full_disk = true; 

    // 智能指针管理代理内部类
    mImpl = std::make_shared<SDKManagerImpl>(); 
    // 初始化内部变量
    mImpl->mCountDown = 0;
    mImpl->mRetryTime = 0;
    mImpl->mAuthValid = false;
}

SDKManager::~SDKManager()
{
    mImpl->SetAuthStatus(false);

    // 确认如果客户没有主动调用shutdown意外退出的话也会有一次服务器回报。
    if (mImpl->mStarted)
    {
        mImpl->Shutdown();
    }
    google::ShutdownGoogleLogging();
}

AUTH_CODE SDKManager::SDKManagerImpl::Init(const std::string& config_filepath)
{
    // 读取配置文件，读取失败则初始化失败。
    bool res = Params::Get().ParaseParamsFile(config_filepath);
    if (false == res)
    {
        LOG(FATAL) << "Failed to load config file: " << config_filepath;
        return AUTH_CODE::INVALID_CONFIG_FILE;
    }
    LOG(INFO) << Params::Get().ParamsString();

    // 从配置文件中获取公钥并进行验证，验证失败则初始化失败。
    mPubKey = Params::Get().GetKeyInfo().key();
    COpenSSL openssl; 
    if (false == openssl.rsa_verify_pubkey(mPubKey))
    {
        LOG(FATAL) << "Invalide public key: " << mPubKey;
        return AUTH_CODE::INVALID_PUBLIC_KEY;
    }

    // 设置默认的服务器汇报倒计时计时器
    mCountDown = Params::Get().GetSystemParams().default_report_countdown_time();
    LOG(INFO) << "Load default_report_countdown_time: " << mCountDown;
    
    // 设置重试次数为0
    mRetryTime = 0;
    // 默认设置无授权模式。 
    SetAuthStatus(false);
    // 设置启动服务器汇报标志。
    mStarted = true;

    // libcurl全局初始化。
    curl_global_init(CURL_GLOBAL_ALL);
    // 主动联系服务器并获取第一次鉴权。
    ConnectServer();

    return AUTH_CODE::SUCCESS;
}

void SDKManager::SDKManagerImpl::ConnectServer()
{
    // 检测连接服务器启动标志。
    if (!mStarted)
    {
        return;
    }

    // 生成本次服务器汇报报告，同时更新当前函数调用次数表的快照。
    std::string report = GenReport();
    LOG(INFO) << "Connect to the server with report: " << report; 

    std::string ret_msg; 
    // 通过POST方式连接服务器发送报告。
    int res = PostServer(report, ret_msg);
    if (0 != res)
    {
        // 服务器返回失败流程
        LOG(ERROR) << "Failed to connect to the server with error code: " << res << ", " << ret_msg;
        AuthFailed();
    }
    else
    {
        // 服务器返回成功，处理服务器返回信息。
        // 此处会自动更新鉴权状态，重试次数，函数调用汇报表已经汇报量扣除和设置服务器新下发倒计时。
        HandleResponse(ret_msg, report);
    }

    // 根据最新更新的倒计时表设置下次报告自动定时器。
    if (!Params::Get().GetInternalDebugOptions().update_server_unit_millisecond())
    {
        timer.StartOnce(mCountDown*1000, std::bind(&SDKManager::SDKManagerImpl::ConnectServer, this));
    }
    else
    {
        // 测试模式，按照毫秒来进行汇报延时
        timer.StartOnce(mCountDown, std::bind(&SDKManager::SDKManagerImpl::ConnectServer, this));
    }
}

void SDKManager::SDKManagerImpl::HouseKeeping()
{
    // 目前没有启用。
    LOG(INFO) << "HouseKeeping() entered. ";
}

bool SDKManager::SDKManagerImpl::GetAuthStatus()
{
    return mAuthValid.load();
}

void SDKManager::SDKManagerImpl::SetAuthStatus(bool status)
{
    mAuthValid.store(status);
}

void SDKManager::SDKManagerImpl::CountUsage(std::string func_name, unsigned int call_count)
{
    do
    {
        // 设置加锁更新函数调用表。
        std::lock_guard<std::mutex> lock(mRecordMutex);
        mCallRecord[func_name] += call_count;

        // 某个函数调用次数到达限量之后的服务器汇报机制。
        // 由于目前的timer组件并不提供任务优先级和任务排队功能，所以此处只是简单的插入一个立刻执行的汇报任务。
        // 未来在有需要的时候，扩展timer组件就可以做到任务排队和提前的功能，避免额外的服务器连接。
        if (mCallRecord[func_name] > Params::Get().GetSystemParams().default_report_call_count())
        {

            timer.StartOnce(0, std::bind(&SDKManager::SDKManagerImpl::ConnectServer, this));
        }
    } while(false);

}

void SDKManager::SDKManagerImpl::ResetCountdown(unsigned int countdown_tick)
{
    mCountDown = countdown_tick;
}

std::string SDKManager::SDKManagerImpl::GenReport()
{
    // 获取当前报告生成时候的信息快照，以便在服务器连接成功之后的信息更新。
    do
    {
        std::lock_guard<std::mutex> lock(mRecordMutex);
        mSnapshot = mCallRecord; 
    } while(false);
    
    // 生成服务器通信所需的json结构
    nlohmann::json json_report;
    json_report["version"] = Params::Get().GetSystemParams().communicate_protocol_version();
    json_report["keyInfo"]["keyType"] = "RSA";
    json_report["keyInfo"]["keyIndex"] = Params::Get().GetKeyInfo().key_index();
    json_report["sdkName"] = Params::Get().GetKeyInfo().sdk_name();
    json_report["vendorName"] = Params::Get().GetKeyInfo().vendor_name();
    auto timeNow = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    json_report["curTime"] = timeNow.count();

    // 初始化一个json空列表存储后续函数调用信息
    json_report["funcNameList"] = nlohmann::json::value_t::array;
    int index = 0;
    for (const auto& item : mSnapshot)
    {
        json_report["funcNameList"][index]["funcName"] = item.first;
        json_report["funcNameList"][index]["callCount"] = item.second;
        ++index;
    }
    DLOG(INFO) << "Original report: " << json_report.dump();
    
    COpenSSL openssl; 
    // 此处的数据加密流程：
    // 1. 使用压缩方式的json字符串作为原始明文字符串clear_text。
    // 2. 将明文字符串经过SHA384哈希后得到哈希字符串存到hash_text中。
    // 3. 将哈希字符串使用配置文件中获取到的公钥加密，密文存储到encript_text中。
    // 4. 将密文经过base64进行编码，编码后的字符串存储到cipher_text中。   
    // 5. 将校验信息添加到最终需要发送的json结构中"cipherText"字段。
    std::string clear_text = json_report.dump(); // (1)
    std::string hash_text; 
    openssl.sha384(clear_text, hash_text); // (2)
    std::string encript_text = openssl.rsa_pub_encrypt(hash_text, mPubKey); // (3)
    std::string cipher_text = base64_encode((const unsigned char *)encript_text.c_str(), encript_text.length()); // (4)
    json_report["cipherText"] = cipher_text; // (5)

    return json_report.dump();
}
    
int SDKManager::SDKManagerImpl::PostServer(const std::string& report, std::string& return_msg)
{
    // 初始化curl调用结构。
    CURL *easy_handle = curl_easy_init();
    if(NULL == easy_handle)
    {
        LOG(FATAL) << "CURL initialization failed. ";
        return_msg = "CURL initialization failed. ";
        return CURLE_FAILED_INIT;
    }

    // 设置POST调用参数。
    CURLcode res;
    curl_slist *http_headers = NULL;
    http_headers = curl_slist_append(http_headers, "Content-Type: application/json");
    std::string server_url = Params::Get().GetSystemParams().server_address();
    std::string post_response; 

    curl_easy_setopt(easy_handle, CURLOPT_HTTPHEADER, http_headers);
    curl_easy_setopt(easy_handle, CURLOPT_URL, server_url.c_str());
    curl_easy_setopt(easy_handle, CURLOPT_POSTFIELDS, report.c_str());
    curl_easy_setopt(easy_handle, CURLOPT_POSTFIELDSIZE, sizeof(char)*report.length());
    curl_easy_setopt(easy_handle, CURLOPT_READFUNCTION, NULL);
    // 设置POST调用数据返回接口回调函数读取服务器返回信息。
    curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, OnWriteData);
    curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, (void *)&return_msg);
    curl_easy_setopt(easy_handle, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(easy_handle, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(easy_handle, CURLOPT_TIMEOUT, 3);

    LOG(INFO) << "Post request established. ";

    // 执行POST服务器调用
    res = curl_easy_perform(easy_handle);
    
    // 清理POST调用结构相关内存
    curl_slist_free_all(http_headers);
    curl_easy_cleanup(easy_handle);
    
    if (res != CURLE_OK)
    {
        return_msg = curl_easy_strerror(res);
        LOG(ERROR) << "Post request failed: " << return_msg;
        return res;
    }
    else
    {
        LOG(INFO) << "Post request success.";
        DLOG(INFO) << "Post response: " << return_msg;
        return 0;
    }
}

int SDKManager::SDKManagerImpl::HandleResponse(const std::string& response, const std::string& orig_report)
{
    LOG(INFO) << "HandleResponse entered. ";
    nlohmann::json json_response;
    LOG(INFO) << "json response established. ";
    unsigned int status; 

    // 第一次从服务器返回的json信息中读取服务器返回状态。
    try
    {
        json_response = nlohmann::json::parse(response);
        status = json_response.at("status");
    }
    catch(nlohmann::detail::exception& e)
    {
        LOG(ERROR) << "1st Json phase response failed: " << e.what(); 
        AuthFailed();
        return -1;
    }

    // 如果服务器返回状态不是200，进入鉴权获取失败流程。
    if (200 != status)
    {
        LOG(ERROR) << "Server response error code: " << status; 
        AuthFailed();
        return status;
    }

    unsigned int version;
    unsigned int new_countdown;
    std::string signature; 

    // 第二次从服务器返回的json信息中读取沟通协议版本，下次服务器汇报倒计时点和服务器签名信息。
    try
    {
        version = json_response.at("data").at("version");
        new_countdown = json_response.at("data").at("reportCountDown");
        signature = json_response.at("data").at("signature");
    }
    catch(nlohmann::detail::out_of_range& e)
    {
        LOG(ERROR) << "2nd Json phase response failed: " << e.what();
        AuthFailed();
        return -1;
    }

    // 如果服务器沟通协议版本不对则进入鉴权获取失败流程。
    if (version != Params::Get().GetSystemParams().communicate_protocol_version())
    {
        LOG(ERROR) << "Protocal version not match, local version: " 
                   << Params::Get().GetSystemParams().communicate_protocol_version()
                   << ", response version: " << version; 
        return -1;
    }

    // 重建发送的原始信息，并移除加密字段
    nlohmann::json json_report = nlohmann::json::parse(orig_report);
    json_report.erase("cipherText");
    DLOG(INFO) << "Resumed the original clear text: " << json_report.dump();

    COpenSSL openssl;
    // 对原始信息进行SHA384哈希处理
    std::string hash_text; 
    openssl.sha384(json_report.dump(), hash_text);

    // 用原始信息的哈希结果和公钥去验证服务器的签名
    bool verify_result = openssl.verifySignature(mPubKey, hash_text, signature);
    if (true == verify_result)
    {
        // 签名验证成功，确认鉴权获取成功
        LOG(INFO) << "Signature verified, extend auth. ";
        AuthExtend(new_countdown);
    }
    else
    {
        // 签名验证失败，进入鉴权失败流程
        LOG(ERROR) << "Signature not match: " << json_report.dump() << ", signature: " << signature;
        AuthFailed();
        return -1; 
    }

    return 0;
}

// 从服务器获取鉴权成功后流程
void SDKManager::SDKManagerImpl::AuthExtend(unsigned int new_countdown)
{
    LOG(INFO) << "Extend authentication, next report countdown: " << new_countdown; 
    // 设置鉴权状态信息。
    SetAuthStatus(true);
    // 重置服务器连接失败重试次数。
    mRetryTime = 0;
    // 设置新的服务器倒计时点数。
    ResetCountdown(new_countdown);

    // 根据生成报告时候的快照，更新处理当前函数调用信息表，将已经汇报的次数扣除。
    for (auto& item : mSnapshot)
    {
        do
        {
            std::lock_guard<std::mutex> lock(mRecordMutex);
            if (mCallRecord[item.first] >= item.second)
            {
                mCallRecord[item.first] -= item.second;
            }
            else
            {
                LOG(ERROR) << "Function record abnormal: " << item.first 
                           << ", record num: " << mCallRecord[item.first] 
                           << ", report num: " << item.second 
                           << ", reset to 0. ";
                mCallRecord[item.first] = 0;
            }
        } while(false);
    }
}

// 从服务器获取鉴权失败后流程
void SDKManager::SDKManagerImpl::AuthFailed()
{
    // 增加重试次数
    ++mRetryTime;
    LOG(INFO) << "AuthFailed, already retried: " << mRetryTime << " times. ";
    
    // 如果重试次数到达上限（配置文件中配置值或者硬编码10次）则终止鉴权下发。
    if (mRetryTime >= Params::Get().GetSystemParams().comm_retry_count() || mRetryTime > 9)
    {
        LOG(ERROR) << "Retry time reach the limitation, authentication disabled. ";
        SetAuthStatus(false);
    }
}

void SDKManager::SDKManagerImpl::Shutdown()
{
    // 首先终止鉴权下发。
    SetAuthStatus(false);

    // 设置模块终止标志，取消后续服务器调用。
    mStarted = false; 

    // 停止计时器。
    timer.StopTimer();

    // 退出前立刻进行一次汇报并丢弃服务器返回。
    std::string report = GenReport();
    LOG(INFO) << "Shutdonw triggered, connect to the server with report: " << report; 
    std::string ret_msg; 
    int res = PostServer(report, ret_msg);
    LOG(WARNING) << "Shutdown triggered report response, return code: " << res;
}

//} // namespace SDKManager

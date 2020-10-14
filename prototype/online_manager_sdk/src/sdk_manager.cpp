
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
class SDKManager::SDKManagerImpl
{
public:
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

    Timer timer; 
    std::string mPubKey;
    std::mutex mRecordMutex; 
    std::unordered_map<std::string, unsigned int> mCallRecord;
    std::unordered_map<std::string, unsigned int> mSnapshot;
    unsigned int mRetryTime;
    std::atomic<unsigned int> mCountDown;
    std::atomic<bool> mAuthValid; 
};

SDKManager& SDKManager::Get()
{
    static SDKManager instance;
    return instance;
}

AUTH_CODE SDKManager::Init(const std::string& config_filepath)
{
    LOG(INFO) << "SDK Initialize, configure file: " << config_filepath;
    bool res = Params::Get().ParaseParamsFile(config_filepath);
    if (false == res)
    {
        LOG(FATAL) << "Failed to load config file: " << config_filepath;
        return AUTH_CODE::INVALID_CONFIG_FILE;
    }

    mImpl->mPubKey = Params::Get().GetKeyInfo().key();
    COpenSSL openssl; 
    if (false == openssl.rsa_verify_pubkey(mImpl->mPubKey))
    {
        LOG(FATAL) << "Invalide public key: " << mImpl->mPubKey;
        return AUTH_CODE::INVALID_PUBLIC_KEY;
    }
    mImpl->mCountDown = Params::Get().GetSystemParams().default_report_countdown_time();
    LOG(INFO) << "Load default_report_countdown_time: " << mImpl->mCountDown;
    mImpl->mRetryTime = 0; 
    mImpl->mAuthValid = false; 

    curl_global_init(CURL_GLOBAL_ALL);

    mImpl->ConnectServer();

    return AUTH_CODE::SUCCESS;
    //mImpl->timer.StartOnce(mImpl->mCountDown, 
    //    std::bind(&SDKManager::SDKManagerImpl::ConnectServer, mImpl));
}

bool SDKManager::Auth()
{
    if (false == mImpl->GetAuthStatus())
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

void SDKManager::Count(const std::string func_name, unsigned int call_count)
{
    DLOG(INFO) << "Count func_name: " << func_name << ", call_count: " << call_count;
    mImpl->CountUsage(func_name, call_count);
}

void SDKManager::Shutdown()
{
    LOG(WARNING) << "SDK manager shutdown. "; 
    mImpl->Shutdown();
}

SDKManager::SDKManager()
{
    DLOG(INFO) << "SDKManager() entered."; 
    google::InitGoogleLogging("sdk_manager"); 
    // 是否将日志输出到stderr而非文件。
    FLAGS_logtostderr = true; 
    //是否将日志输出到文件和stderr，如果：true，忽略FLAGS_stderrthreshold的限制，所有信息打印到终端。
    FLAGS_alsologtostderr = false;
    //设置可以缓冲日志的最大秒数，0指实时输出。 
    FLAGS_logbufsecs = 0; 
    //设置最大日志文件大小（以MB为单位）。
    FLAGS_max_log_size = 100; 
    //设置是否在磁盘已满时避免日志记录到磁盘。
    FLAGS_stop_logging_if_full_disk = true; 

    mImpl = std::make_shared<SDKManagerImpl>(); 
    mImpl->mCountDown = 0;
    mImpl->mRetryTime = 0;
    mImpl->mAuthValid = false;
}

SDKManager::~SDKManager()
{
    mImpl->mAuthValid = false; 
    google::ShutdownGoogleLogging();
}

void SDKManager::SDKManagerImpl::ConnectServer()
{
    std::string report = GenReport();
    LOG(INFO) << "Connect to the server with report: " << report; 

    std::string ret_msg; 
    int res = PostServer(report, ret_msg);
    if (0 != res)
    {
        LOG(ERROR) << "Failed to connect to the server with error code: " << res << ", " << ret_msg;
        AuthFailed();
    }
    else
    {
        HandleResponse(ret_msg, report);
    }
    timer.StartOnce(mCountDown*1000, std::bind(&SDKManager::SDKManagerImpl::ConnectServer, this));
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
        std::lock_guard<std::mutex> lock(mRecordMutex);
        mCallRecord[func_name] += call_count;
    } while(false);
}

void SDKManager::SDKManagerImpl::ResetCountdown(unsigned int countdown_tick)
{
    mCountDown = countdown_tick;
}

std::string SDKManager::SDKManagerImpl::GenReport()
{
    do
    {
        std::lock_guard<std::mutex> lock(mRecordMutex);
        mSnapshot = mCallRecord; 
    } while(false);
    
    nlohmann::json json_report;
    json_report["version"] = Params::Get().GetSystemParams().communicate_protocol_version();
    json_report["keyInfo"]["keyType"] = "RSA";
    json_report["keyInfo"]["keyIndex"] = Params::Get().GetKeyInfo().key_index();
    json_report["vendorName"] = Params::Get().GetKeyInfo().vendor_name();
    json_report["curTime"] = (int)std::time(0);

    json_report["funcNameList"] = nlohmann::json::value_t::array;
    int index = 0;
    for (const auto& item : mSnapshot)
    {
        json_report["funcNameList"][index]["funcName"] = item.first;
        json_report["funcNameList"][index]["callCount"] = item.second;
        ++index;
    }
    //DLOG(INFO) << "Original report: " << json_report.dump();
    
    COpenSSL openssl; 
    // 使用压缩方式的json字符串作为原始明文字符串。
    std::string clear_text = json_report.dump();

    // 将明文字符串经过SHA384哈希后得到哈希字符串存到hash_text中。
    std::string hash_text; 
    openssl.sha384(clear_text, hash_text);

    // 将哈希字符串使用配置文件中获取到的公钥加密，密文存储到encript_text中。
    std::string encript_text = openssl.rsa_pub_encrypt(hash_text, mPubKey);

    // 将密文经过base64进行编码，编码后的字符串存储到cipher_text中。
    std::string cipher_text = base64_encode((const unsigned char *)encript_text.c_str(), encript_text.length());
    
    // 将校验信息添加到最终需要发送的json结构中。
    json_report["cipherText"] = cipher_text; 

    return json_report.dump();
}
    
int SDKManager::SDKManagerImpl::PostServer(const std::string& report, std::string& return_msg)
{
    CURL *easy_handle = curl_easy_init();
    if(NULL == easy_handle)
    {
        LOG(FATAL) << "CURL initialization failed. ";
        return_msg = "CURL initialization failed. ";
        return CURLE_FAILED_INIT;
    }
    CURLcode res;
    curl_slist *http_headers = NULL;
    http_headers = curl_slist_append(http_headers, "Content-Type: application/json");
    std::string server_url = 
        Params::Get().GetSystemParams().server_address() + 
        ":" + std::to_string(Params::Get().GetSystemParams().server_port());
    std::string post_response; 

    curl_easy_setopt(easy_handle, CURLOPT_HTTPHEADER, http_headers);
    curl_easy_setopt(easy_handle, CURLOPT_URL, server_url.c_str());
    curl_easy_setopt(easy_handle, CURLOPT_POSTFIELDS, report.c_str());
    curl_easy_setopt(easy_handle, CURLOPT_POSTFIELDSIZE, sizeof(char)*report.length());
    curl_easy_setopt(easy_handle, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, OnWriteData);
    curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, (void *)&return_msg);
    curl_easy_setopt(easy_handle, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(easy_handle, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(easy_handle, CURLOPT_TIMEOUT, 3);

    LOG(INFO) << "Post request established. ";

    res = curl_easy_perform(easy_handle);
    
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
    int version;
    int status; 
    int new_countdown;
    std::string signature; 
    try
    {
        nlohmann::json json_response = nlohmann::json::parse(response);
        version = json_response.at("data").at("version");
        status = json_response.at("status");
        new_countdown = json_response.at("data").at("reportCountDown");
        signature = json_response.at("data").at("signature");
    }
    catch(nlohmann::detail::exception& e)
    {
        //LOG(ERROR) << "Phase response failed: " << e.what() << ", exeception id: " << e.id << ", byte position of error: " << e.byte; 
        LOG(ERROR) << "Phase response failed: " << e.what(); 
        AuthFailed();
        return -1;
    }
    
    if (version != Params::Get().GetSystemParams().communicate_protocol_version())
    {
        LOG(ERROR) << "Protocal version not match, local version: " 
                   << Params::Get().GetSystemParams().communicate_protocol_version()
                   << ", response version: " << version; 
        return -1;
    }

    if (200 != status)
    {
        LOG(ERROR) << "Server response error code: " << status; 
        AuthFailed();
        return status;
    }
    
    nlohmann::json json_report = nlohmann::json::parse(orig_report);
    json_report.erase("cipherText");
    DLOG(INFO) << "Resumed the original clear text: " << json_report.dump();

    COpenSSL openssl;
    bool verify_result = openssl.verifySignature(mPubKey, json_report.dump(), signature);
    if (true == verify_result)
    {
        LOG(INFO) << "Signature verified, extend auth. ";
        AuthExtend(new_countdown);
    }
    else
    {
        LOG(ERROR) << "Signature not match: " << json_report.dump() << ", signature: " << signature;
        AuthFailed();
        return -1; 
    }

    return 0;
}

void SDKManager::SDKManagerImpl::AuthExtend(unsigned int new_countdown)
{
    LOG(INFO) << "Extend authentication, next report countdown: " << new_countdown; 
    SetAuthStatus(true);
    mRetryTime = 0;
    ResetCountdown(new_countdown);

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

void SDKManager::SDKManagerImpl::AuthFailed()
{
    ++mRetryTime;
    LOG(INFO) << "AuthFailed, already retried: " << mRetryTime << " times. ";
    if (mRetryTime >= (unsigned int)Params::Get().GetSystemParams().comm_retry_count() || mRetryTime > 9)
    {
        LOG(ERROR) << "Retry time reach the limitation, authentication disabled. ";
        SetAuthStatus(false);
    }
}

void SDKManager::SDKManagerImpl::Shutdown()
{
    SetAuthStatus(false);
    timer.StopTimer();
    std::string report = GenReport();
    LOG(INFO) << "Shutdonw triggered, connect to the server with report: " << report; 
    std::string ret_msg; 
    int res = PostServer(report, ret_msg);
    LOG(WARNING) << "Shutdown triggered report response, return code: " << res <<", response: " << ret_msg;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

//} // namespace SDKManager

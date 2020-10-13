
#include <iostream> 
#include <iomanip>
#include <unordered_map>
#include <mutex> 
#include <atomic> 
#include <thread> 
#include <ctime> 
#include <exception>

#include <curl/curl.h>

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
    bool res = Params::Get().ParaseParamsFile(config_filepath);
    if (false == res)
    {
        return AUTH_CODE::INVALID_CONFIG_FILE;
    }
    std::cout << "====== Read config file ======" << std::endl;
    Params::Get().PrintParams();

    mImpl->mPubKey = Params::Get().GetKeyInfo().key();
    COpenSSL openssl; 
    if (false == openssl.rsa_verify_pubkey(mImpl->mPubKey))
    {
        return AUTH_CODE::INVALID_PUBLIC_KEY;
    } 
    mImpl->mCountDown = Params::Get().GetSystemParams().default_report_countdown_time();
    mImpl->mRetryTime = 0; 
    mImpl->mAuthValid = false; 

    curl_global_init(CURL_GLOBAL_ALL);

    mImpl->ConnectServer();

    return AUTH_CODE::SUCCESS;
    //mImpl->timer.StartOnce(mImpl->mCountDown, 
    //    std::bind(&SDKManager::SDKManagerImpl::ConnectServer, mImpl));
}

AUTH_CODE SDKManager::Auth()
{
    if (false == mImpl->GetAuthStatus())
    {
        return AUTH_CODE::SUCCESS;
    }
    else
    {
        return AUTH_CODE::AUTH_EXPIRED;
    }
}

void SDKManager::Count(const std::string func_name, unsigned int call_count)
{
    mImpl->CountUsage(func_name, call_count);
}

void SDKManager::Shutdown()
{
    mImpl->mAuthValid = false;
}

SDKManager::SDKManager()
{
    mImpl = std::make_shared<SDKManagerImpl>(); 
    mImpl->mCountDown = 0;
    mImpl->mRetryTime = 0;
    mImpl->mAuthValid = false;
}

SDKManager::~SDKManager()
{
    mImpl->mAuthValid = false; 
    //delete mImpl;
}

void SDKManager::SDKManagerImpl::ConnectServer()
{
    std::cout << "Connecting the server. " << std::endl;
    std::string report = GenReport();
    std::string ret_msg; 
    int res = PostServer(report, ret_msg);
    if (0 != res)
    {
        std::cout << "Error on connect server: " << ret_msg << std::endl;
    }
    else
    {
        //std::cout << "ret_msg: " << ret_msg << std::endl;
        HandleResponse(ret_msg, report);
    }
    timer.StartOnce(mCountDown*1000, std::bind(&SDKManager::SDKManagerImpl::ConnectServer, this));
}

void SDKManager::SDKManagerImpl::HouseKeeping()
{
    std::cout << "House keeping. " << std::endl;
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
    std::cout << "Count usage of: " << func_name << " increased " << call_count << std::endl;
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
    std::cout << "ORIGINAL : " << json_report.dump() << std::endl;
    
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

    std::cout << "====== REPORT ======" << std::endl;
    // std::cout << std::setw(4) << json_report << '\n';
    std::cout << json_report.dump() << std::endl;
    std::cout << std::endl << std::endl; 
    return json_report.dump();
}
    
int SDKManager::SDKManagerImpl::PostServer(const std::string& report, std::string& return_msg)
{
    CURL *easy_handle = curl_easy_init();
    if(NULL == easy_handle)
    {
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

    res = curl_easy_perform(easy_handle);
    
    curl_slist_free_all(http_headers);
    curl_easy_cleanup(easy_handle);
    
    if (res != CURLE_OK)
    {
        return_msg = curl_easy_strerror(res);
        return res;
    }
    else
    {
        std::cout << "====== RESPONSE ======\n" << return_msg << std::endl;
        return 0;
    }
}

int SDKManager::SDKManagerImpl::HandleResponse(const std::string& response, const std::string& orig_report)
{
    nlohmann::json json_response = nlohmann::json::parse(response);

    //int version = json_response["data"]["version"];
    int version;
    int status; 
    std::string signature; 
    try
    {
        version = json_response.at("data").at("version");
        status = json_response.at("status");
        signature = json_response.at("data").at("signature");
    }
    catch(nlohmann::detail::out_of_range)
    {
        ++mRetryTime;
        if (mRetryTime >= (unsigned int)Params::Get().GetSystemParams().comm_retry_count() || mRetryTime > 9)
        {
            mAuthValid = false;
        }
        return -1;
    }
    
    if (version != Params::Get().GetSystemParams().communicate_protocol_version())
    {
        // TODO 记录version不对的信息。
        return -1;
    }

    if (200 != status)
    {
        // TODO 记录服务器返回失败信息。
        mRetryTime += 1; 
        if(mRetryTime > 3)
        {
            mAuthValid = false;
        }
        return status;
    }
    
    nlohmann::json json_report = nlohmann::json::parse(orig_report);
    json_report.erase("cipherText");
    //std::cout << "RECOVERED: " << json_report.dump() << std::endl;

    COpenSSL openssl;
    bool verify_result = openssl.verifySignature(mPubKey, json_report.dump(), signature);
    if (true == verify_result)
    {
        for (auto& item : mSnapshot)
        {
            do
            {
                std::lock_guard<std::mutex> lock(mRecordMutex);
                if (mCallRecord[item.first] >= item.second)
                {
                    mCallRecord[item.first] -= item.second;
                }
            } while(false);
        }
        
        mAuthValid = true;
        mRetryTime = 0;
    }
    else
    {
        ++mRetryTime;
        if (mRetryTime >= (unsigned int)Params::Get().GetSystemParams().comm_retry_count() || mRetryTime > 9)
        {
            mAuthValid = false;
        }
        return -1; 
    }

    return 0;
}

//} // namespace SDKManager

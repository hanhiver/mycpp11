
#include <iostream> 
#include <iomanip>
#include <unordered_map>
#include <mutex> 
#include <atomic> 
#include <thread> 
#include <ctime> 
#include <exception>

#include "timer.hpp"
#include "params.hpp"
#include "json.hpp"
#include "base64.hpp"
#include "COpenSSL.hpp"

#include "sdk_manager.hpp"

//namespace SDKManager
//{
class SDKManager::SDKManagerImpl
{
public:
    void ConnectServer();
    void HouseKeeping();

    bool GetAuthStatus();
    void SetAuthStatus(bool status);
    void CountUsage(const std::string func_name, unsigned int call_count = 1);
    void ResetCountdown(unsigned int countdown_tick);

    std::string GenReport(std::unordered_map<std::string, unsigned int>& snapshot);
    int PostServer(const std::string& report, std::string& return_msg);

    Timer timer; 
    std::string mPubKey;
    std::mutex mRecordMutex; 
    std::unordered_map<std::string, unsigned int> mCallRecord;
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
    std::unordered_map<std::string, unsigned int> snapshot; 
    GenReport(snapshot);
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

std::string SDKManager::SDKManagerImpl::GenReport(std::unordered_map<std::string, unsigned int>& snapshot)
{
    do
    {
        std::lock_guard<std::mutex> lock(mRecordMutex);
        //std::unordered_map<std::string, unsigned int> temp(mCallRecord);
        snapshot = mCallRecord; 
    } while(false);
    
    nlohmann::json json_report;
    json_report["version"] = Params::Get().GetSystemParams().communicate_protocol_version();
    json_report["keyInfo"]["keyType"] = "RSA";
    json_report["keyInfo"]["keyIndex"] = Params::Get().GetKeyInfo().key_index();
    json_report["vendorName"] = Params::Get().GetKeyInfo().vendor_name();
    json_report["curTime"] = (int)std::time(0);

    json_report["funcNameList"] = nlohmann::json::value_t::array;
    int index = 0;
    for (const auto& item : snapshot)
    {
        json_report["funcNameList"][index]["funcName"] = item.first;
        json_report["funcNameList"][index]["callCount"] = item.second;
        ++index;
    }
    
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
    
    return 0; 
}

//} // namespace SDKManager

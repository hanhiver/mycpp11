#include <iostream> 
#include <string.h> 
#include <curl/curl.h>

using namespace std; 

// 回调函数，得到相应内容。
int write_data(void* buffer, int size, int nmemb, void* userp)
{
    std::string *str = dynamic_cast<std::string *>((std::string *)userp);
    str->append((char *)buffer, size*nmemb);
    return nmemb; 
}

int upload(string url, string &body,  string* response)
{
    CURL *curl;
    CURLcode ret;
    curl = curl_easy_init();
    struct curl_httppost* post = NULL;
    struct curl_httppost* last = NULL;
    if (curl)
    {
        //指定url
        curl_easy_setopt(curl, CURLOPT_URL, (char *)url.c_str());   
        //form-data key(path) 和 value(device_cover)        
        curl_formadd(&post, &last, CURLFORM_PTRNAME, "path", CURLFORM_PTRCONTENTS, "device_cover", CURLFORM_END);
        // form-data key(file) "./test.jpg"为文件路径  "hello.jpg" 为文件上传时文件名
        curl_formadd(&post, &last, CURLFORM_PTRNAME,  "file", 
                     CURLFORM_FILE, "/tmp/test.txt",
                     CURLFORM_FILENAME, "./test.txt", CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);                     //构造post参数    
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);          //绑定相应
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)response);        //绑定响应内容的地址

        ret = curl_easy_perform(curl);                          //执行请求
        if(ret == 0){
            curl_easy_cleanup(curl);    
            return 0;  
        }
        else{
            return ret;
        }
    }
	else{
        return -1;
	}
}

int main(int argc, char* argv[])
{
    std::string body; 
    std::string response; 

    int status_code = upload("http://127.0.0.1:8888", body, &response);
	if (status_code != CURLcode::CURLE_OK) {
			return -1;
	}
    cout << body << endl;
	cout << response << endl;

    return 0; 
}

//#include <cstdlib>
//#include <cstdio>
#include <iostream> 
#include <curl/curl.h>

size_t process_data(void *buffer, size_t size, size_t nmemb, void *user_p)
{
    FILE *fp = (FILE *)user_p;
    size_t return_size = fwrite(buffer, size, nmemb, fp);
    std::cout << (char *)buffer << std::endl;

    return return_size;
}

int main(int argc, char *argv[])
{
    // 初始化libcurl
    CURLcode return_code;
    return_code = curl_global_init(CURL_GLOBAL_ALL);
    if (CURLE_OK != return_code)
    {
        std::cerr << "Initialize libcurl failed. " << std::endl;
        return -1; 
    }

    // 获取easy句柄
    CURL *easy_handle = curl_easy_init();
    if (NULL == easy_handle)
    {
        std::cerr << "Failed to get easy handle. " << std::endl;
        curl_global_cleanup();
        return -1;
    }

    FILE *fp = fopen("data.html", "wb+");

    // 设置easy handle属性
    // 设置URL
    curl_easy_setopt(easy_handle, CURLOPT_URL, "http://www.baidu.com");
    curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, &process_data);
    curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, fp);

    // 执行请求。
    curl_easy_perform(easy_handle);

    // 释放资源
    fclose(fp);
    curl_easy_cleanup(easy_handle);
    curl_global_cleanup();

    return 0;
}
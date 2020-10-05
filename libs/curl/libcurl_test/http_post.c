#include <stdio.h>
#include <curl/curl.h>

int main(void)
{
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);

    // 获得一个curl的句柄。 
    curl = curl_easy_init();
    if (curl)
    {
        // 首先设置URL，URL可以是https://开头的。
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8288");
        // 设置使用POST方式
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        // 设置POST的data
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=dhan&project=my_curl");

        // 执行POST请求操作。
        res = curl_easy_perform(curl);

        // 检查返回值。
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", 
                    curl_easy_strerror(res));
        }

        // 保证永远要做清理工作。
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
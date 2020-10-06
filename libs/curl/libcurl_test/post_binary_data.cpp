#include <curl/curl.h>

int main(int argc, char *argv[])
{
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *easy_handle = curl_easy_init();

    // 上传二级制数据。
    char data[] = {1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0};
    curl_slist *http_headers = NULL;
    http_headers = curl_slist_append(http_headers, "Content-Type: text/xml");

    curl_easy_setopt(easy_handle, CURLOPT_HTTPHEADER, http_headers);
    curl_easy_setopt(easy_handle, CURLOPT_URL, "http://localhost:8288/register");
    curl_easy_setopt(easy_handle, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(easy_handle, CURLOPT_POSTFIELDSIZE, sizeof(data));

    curl_easy_perform(easy_handle);

    curl_slist_free_all(http_headers);
    curl_easy_cleanup(easy_handle);
    curl_global_cleanup();

    return 0;
}

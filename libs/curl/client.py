import http.client

conn = http.client.HTTPConnection("127.0.0.1", port=8288)

payload = "abcdddddEEEE"

headers = {
    'Content-Type': "text/plain",
    'User-Agent': "PostmanRuntime/7.15.0",
    'Accept': "*/*",
    'Cache-Control': "no-cache",
    'Postman-Token': "b695333f-e7e4-4926-8824-aea76482402b,48e619a9-f5a1-4898-9184-57cde4d72d89",
    'Host': "192.168.1.108:8080",
    'accept-encoding': "gzip, deflate",
    'content-length': "24",
    'Connection': "keep-alive",
    'cache-control': "no-cache"
    }

conn.request("POST", "TestServer", payload, headers)

res = conn.getresponse()
data = res.read()

print(data.decode("utf-8"))

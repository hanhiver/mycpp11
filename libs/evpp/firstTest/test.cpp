#include <iostream>
#include <strstream>

#include "../evpp/http/http_server.h"

void DefaultHandler(evpp::EventLoop* loop, 
                    const evpp::http::ContextPtr& ctx, 
                    const evpp::http::HTTPSendResponseCallback& cb)
{
    std::cout << "Request recieved from: " << ctx->remote_ip() << std::endl;
    std::stringstream oss;
    oss << "func=" << __FUNCTION__ << " OK" << "\n"
        << " ip=" << ctx->remote_ip() << "\n"
        << " uri=" << ctx->uri() << "\n"
        << " body=" << ctx->body().ToString() << "\n";

    ctx->AddResponseHeader("Content-Type", "application/octet-stream");
    ctx->AddResponseHeader("Server", "evpp");
    cb(oss.str());
}

int main(int argc, char* argv[])
{
    std::vector<int> ports = { 9009, 23456, 23457 };
    int port = 29099;
    int thread_num = 2;

    evpp::http::Server server(thread_num);
    server.SetThreadDispatchPolicy(evpp::ThreadDispatchPolicy::kIPAddressHashing);
    server.RegisterDefaultHandler(&DefaultHandler);
    server.RegisterHandler("/echo", 
                           [](evpp::EventLoop* loop, 
                              const evpp::http::ContextPtr& ctx, 
                              const evpp::http::HTTPSendResponseCallback& cb)
                              {
                                  std::cout << "Echo request received from: " << ctx->remote_ip() << std::endl;
                                  cb(ctx->body().ToString());
                              } );
    server.Init(ports);
    server.Start();
    while (!server.IsStopped())
    {
        usleep(1);
    }
    return 0;
}

    
#include <iostream>
#include <string> 
#include <thread> 
#include "evpp/tcp_conn.h"
#include "evpp/event_loop.h"
#include "evpp/tcp_server.h"


int main()
{
    std::string addr = "0.0.0.0:9090";
    int thread_num = 2;
    evpp::EventLoop loop;
    evpp::TCPServer server(&loop, addr, "TCPEchoServer", thread_num);

    server.SetMessageCallback([](const evpp::TCPConnPtr& conn, evpp::Buffer* msg)
                                {
                                    // Here just send the message back. 
                                    conn->Send(msg);
                                });
    server.SetConnectionCallback([](const evpp::TCPConnPtr& conn) 
                                {
                                    if (conn->IsConnected())
                                    {
                                        LOG_INFO << "A new connection from " << conn->remote_addr();
                                    }
                                    else
                                    {
                                        LOG_INFO << "Lost the connection from " << conn->remote_addr();
                                    }
                                });
    server.Init();
    server.Start();
    loop.Run();
}

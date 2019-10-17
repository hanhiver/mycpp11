#include <iostream> 
#include <thread> 
#include <string> 
#include "evpp/tcp_client.h"
#include "evpp/tcp_conn.h"

/*
int main2()
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
*/

int main()
{
    std::string addr = "127.0.0.1:9090";
    evpp::EventLoop loop; 
    evpp::TCPClient client(&loop, addr, "TCPEchoClient"); 

    client.SetConnectionCallback([](const evpp::TCPConnPtr& conn)
                                    {
                                        if (conn->IsConnected())
                                        {
                                            LOG_INFO << "Connected to " << conn->remote_addr();
                                        }
                                        else
                                        {
                                            conn->loop()->Stop();
                                        }
                                    });

    client.SetMessageCallback([&loop, &client](const evpp::TCPConnPtr& conn, evpp::Buffer* msg)
                                {
                                    LOG_INFO << "Receive a message [" << msg->ToString() << "]";
                                    //conn->Send("Hello!"); 
                                    client.Disconnect();
                                });
    client.Connect();
    loop.Run();
    //client.Disconnect();
}
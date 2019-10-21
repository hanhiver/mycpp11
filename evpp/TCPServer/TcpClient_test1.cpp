#include <iostream> 
#include <thread> 
#include <string> 
#include "evpp/buffer.h"
#include "evpp/tcp_client.h"
#include "evpp/tcp_conn.h"

int main()
{
    std::string addr = "0.0.0.0:9090";
    evpp::EventLoop loop; 
    evpp::TCPClient client(&loop, addr, "TCPEchoClient"); 

    std::cout << "ServerMain: " << std::this_thread::get_id() << std::endl; 

    client.SetConnectionCallback([](const evpp::TCPConnPtr& conn)
                                    {
                                        if (conn->IsConnected())
                                        {
                                            std::cout << "ConnectionCallback: " << std::this_thread::get_id() << std::endl; 
                                            LOG_INFO << "Connected to " << conn->remote_addr();
                                            conn->Send("Hello!");
                                        }
                                        else
                                        {
                                            conn->loop()->Stop();
                                        }
                                    });

    client.SetMessageCallback([&loop, &client](const evpp::TCPConnPtr& conn, evpp::Buffer* msg)
                                {
                                    std::cout << "MessageCallback: " << std::this_thread::get_id() << std::endl; 
                                    LOG_INFO << "Receive a message [" << msg->ToString() << "]";
                                    //conn->Send("Hello!"); 
                                    client.Disconnect();
                                });
    client.Connect();
    loop.Run();
    //client.Disconnect();
}
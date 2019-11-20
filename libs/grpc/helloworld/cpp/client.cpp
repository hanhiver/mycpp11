#include <iostream> 
#include <memory> 
#include <string> 

#include <grpcpp/grpcpp.h>
#include "helloworld.grpc.pb.h"

class GreeterClient 
{
public:
    GreeterClient(std::shared_ptr<grpc::Channel> channel) 
    : stub_(Greeter::NewStub(channel))
    {}

    std::string SayHello(const std::string& user)
    {
        HelloRequest request; 
        request.set_name(user);

        HelloReply reply; 
        grpc::ClientContext context; 

        grpc::Status status = stub_->SayHello(&context, request, &reply);

        if (status.ok())
        {
            return reply.message();
        }
        else
        {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl; 
            return "RPC failed"; 
        }
    }

private: 
    std::unique_ptr<Greeter::Stub> stub_; 
};

int main(int argc, char** argv)
{
    std::cout << "Main started. " << std::endl;
    auto channel = grpc::CreateChannel("localhost:30088", 
                                       grpc::InsecureChannelCredentials());
    std::cout << "Channel created. " << std::endl; 
    GreeterClient greeter(channel);
    std::cout << "Greeter created. " << std::endl; 
    
    std::string user("world"); 
    std::string reply = greeter.SayHello(user);
    std::cout << "Greeter received: " << reply << std::endl; 

    return 0; 
}

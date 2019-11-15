#include <iostream> 
#include <memory> 
#include <string> 
#include <grpcpp/grpcpp.h>

#include "helloworld.grpc.pb.h"


class GreeterServiceImpl final : public Greeter::Service 
{
    grpc::Status SayHello(grpc::ServerContext* context, 
                          const HelloRequest* request, 
                          HelloReply* reply) override
    {
        std::string prefix("Hello "); 
        reply->set_message(prefix + request->name());
        return grpc::Status::OK; 
    }
}; 

void RunServer()
{
    std::cout << "RunServer started. " << std::endl; 
    std::string server_address("0.0.0.0:50051");

    GreeterServiceImpl service; 
    grpc::ServerBuilder builder; 

    std::cout << "Service and builder created. " << std::endl; 

    // Listen on the given address without any authantication mechanism. 
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials()); 

    std::cout << "AddListeningPort. " << std::endl; 

    // Register "service" as the instance through which we'll communicate with. 
    // In this case, it corresponds to an "synchronous" service. 
    builder.RegisterService(&service); 
    std::cout << "RegisterService. " << std::endl; 

    // Finally assemble the server. 
    auto bd = builder.BuildAndStart(); 
    std::cout << "BuildAndStart()" << std::endl; 
    //std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::unique_ptr<grpc::Server> server(std::move(bd));
    std::cout << "Server listening on " << server_address << std::endl; 

    // Wait for the server to shutdown. 
    server->Wait();
}

int main(int argc, char** argv)
{
    RunServer();

    return 0; 
}

import logging  
import grpc  

import helloworld_pb2
import helloworld_pb2_grpc 

def run():
    with grpc.insecure_channel('127.0.0.1:50051') as channel: 
        stub = helloworld_pb2_grpc.GreeterStub(channel)
        response = stub.SayHello(helloworld_pb2.HelloRequest(name='dhan'))

    print("Greeter client received: " + response.message)

if __name__ == '__main__':
    logging.basicConfig()
    run()
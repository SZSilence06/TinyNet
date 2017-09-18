#include <TinyNet.h>
#include <iostream>

using namespace TinyNet;

int main()
{
    EventDispatcher dispatcher;
    auto server = TcpServer4::create(&dispatcher, "", 3000);
    server->setOnRead([](TcpConnection* connection){
        std::cout<< "Received data." << std::endl;
    });
    server->start();
    return dispatcher.run();
}

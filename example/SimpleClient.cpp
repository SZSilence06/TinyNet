#include <TinyNet.h>
#include <iostream>

using namespace TinyNet;

int main()
{
    EventDispatcher dispatcher;
    auto client= TcpClient::create(&dispatcher);
    client->setNonBlock(true);
    client->setOnConnected([](){
        std::cout << "Connected!" << std::endl;
    });
    client->connect("192.168.153.128", 3000);
    return dispatcher.run();
}

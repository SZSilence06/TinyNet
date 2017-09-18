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
    client->connect("127.0.0.1", 3000);
    return dispatcher.run();
}

#include <TinyNet.h>

using namespace TinyNet;

int main()
{
    EventDispatcher dispatcher;
    auto server = TcpServer4::create(&dispatcher, "192.168.153.128", 3000);
    server->start();
    return dispatcher.run();
}

#include <Addr.h>
#include <arpa/inet.h>
#include <Logger.h>

namespace TinyNet
{
    Ip4Addr::Ip4Addr(const std::string &address)
    {
        if(address == "")
            addr_.s_addr = INADDR_ANY;
        else
            addr_.s_addr = inet_addr(address.c_str());
    }

    Ip4Addr Ip4Addr::Any()
    {
        Ip4Addr result;
        result.addr_.s_addr = INADDR_ANY;
        return result;
    }

    std::string Ip4Addr::toString() const
    {
        return std::string(inet_ntoa(addr_));
    }

    //////////////////////////////////////////////////
    Sock4Addr::Sock4Addr(const Ip4Addr &addr, uint16_t port)
    {
        addr_.sin_family = AF_INET;
        addr_.sin_port = htons(port);
        addr_.sin_addr = addr.getAddr();
    }
}

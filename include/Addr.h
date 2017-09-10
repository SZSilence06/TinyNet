#ifndef TN_ADDR_H
#define TN_ADDR_H

#include <Common.h>
#include <netinet/in.h>
#include <string>

namespace TinyNet
{
    TN_API class IpAddr
    {
        virtual std::string toString() const = 0;
    };

    TN_API class Ip4Addr : public IpAddr
    {
    public:
        Ip4Addr() = default;
        Ip4Addr(const struct in_addr& address) { addr_ = address; }
        Ip4Addr(const std::string& address);

        static Ip4Addr Any();

        virtual std::string toString() const override;

        const struct in_addr& getAddr() const { return addr_; }

    private:
        struct in_addr addr_;
    };

    TN_API class Ip6Addr : public IpAddr
    {
    public:
        Ip6Addr() = default;
        Ip6Addr(const std::string& address);
    };

    TN_API class SockAddr
    {
    };

    TN_API class Sock4Addr
    {
    public:
        Sock4Addr() = default;
        Sock4Addr(const Ip4Addr& addr, uint16_t port);

        Ip4Addr getIp() const { return Ip4Addr(addr_.sin_addr); }
        uint16_t getPort() const { return addr_.sin_port; }
        const struct sockaddr_in& getAddr() const { return addr_; }

    private:
        struct sockaddr_in addr_;
    };
}

#endif

#include <Socket.h>
#include <Addr.h>
#include <Logger.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

namespace TinyNet
{
    Socket::~Socket()
    {
        if(fd_ >= 0)
            close(fd_);
    }

    bool Socket::listen()
    {
        if(fd_ < 0)
        {
            TN_FATAL("Try to listen an invalid socket!");
            return false;
        }
        if(::listen(fd_, max_queue_size_) == -1)
        {
            TN_ERROR("Socket listen failed.");
            return false;
        }        
        return true;
    }
    //////////////////////////////////////////////////
    std::string Socket4::getIp() const
    {
        struct sockaddr_in addr;
        socklen_t addr_len = sizeof(addr);
        getsockname(fd_, (sockaddr*)&addr, &addr_len);
        Ip4Addr ip(addr.sin_addr);
        return ip.toString();
    }

    uint16_t Socket4::getPort() const
    {
        struct sockaddr_in addr;
        socklen_t addr_len = sizeof(addr);
        getsockname(fd_, (sockaddr*)&addr, &addr_len);
        return ntohs(addr.sin_port);
    }

    //////////////////////////////////////////////////
    TcpSocket4* TcpSocket4::create(const Sock4Addr &addr)
    {
        int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(fd == -1)
            return nullptr;

        if(bind(fd, (struct sockaddr*)&addr.getAddr(), sizeof(struct sockaddr_in)) == -1)
        {
            TN_ERROR("Failed to bind socket!");
            close(fd);
            return nullptr;
        }

        TcpSocket4* result = new TcpSocket4();
        result->fd_ = fd;
        return result;
    }

    TcpSocket4* TcpSocket4::create(int fd)
    {
        TcpSocket4* result = new TcpSocket4();
        result->fd_ = fd;
        return result;
    }
}

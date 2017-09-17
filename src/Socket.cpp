#include <Socket.h>
#include <Addr.h>
#include <Logger.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
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

    bool Socket::setNonBlock(bool nonBlock)
    {
        if(fd_ < 0)
        {
            TN_FATAL("Try to operate on an invalid socket!");
            return false;
        }
        int flags = fcntl(fd_, F_GETFL, 0);
        if(nonBlock)
            if(fcntl(fd_, F_SETFL, flags | O_NONBLOCK) == -1)
                return false;
        else
            if(fcntl(fd_, F_SETFL, flags & (~O_NONBLOCK)) == -1)
                return false;
        return true;
    }

    bool Socket::checkConnection()
    {
        int result;
        socklen_t result_len = sizeof(result);
        if (getsockopt(fd_, SOL_SOCKET, SO_ERROR, &result, &result_len) < 0) {
            // error, fail somehow, close socket
            TN_ERROR("Failed to call getsockopt()!");
            return false;
        }

        if (result != 0) {
            // connection failed; error code is in 'result'
            TN_ERROR("Connection failed! Error code is" + std::to_string(result));
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

    Sock4Addr Socket4::getAddr() const
    {
        if(fd_ == -1)
        {
            TN_FATAL("Try to get address of invalid socket!");
        }
        struct sockaddr_in addr;
        socklen_t addr_len = sizeof(addr);
        getsockname(fd_, (sockaddr*)&addr, &addr_len);
        return Sock4Addr(addr);
    }

    Sock4Addr Socket4::getPeerAddr() const
    {
        if(fd_ == -1)
        {
            TN_FATAL("Try to get address of invalid socket!");
        }
        struct sockaddr_in addr;
        socklen_t addr_len = sizeof(addr);
        getpeername(fd_, (sockaddr*)&addr, &addr_len);
        return Sock4Addr(addr);
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

    bool TcpSocket4::connect(const Sock4Addr &addr)
    {
        return ::connect(fd_, (struct sockaddr*)&addr.getAddr(), sizeof(struct sockaddr_in))
                != -1;
    }
}

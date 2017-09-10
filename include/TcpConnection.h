#ifndef TN_TCP_CONNECTION_H
#define TN_TCP_CONNECTION_H

#include <Common.h>
#include <memory>

namespace TinyNet
{
    class TcpSocket4;

    TN_API class TcpConnection
    {
    public:
        static TcpConnection* create(TcpSocket4* socket);

    private:
        TcpConnection() = default;

    private:
        std::unique_ptr<TcpSocket4> socket_ = nullptr;
    };
}

#endif

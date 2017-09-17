#ifndef TN_TCP_CONNECTION_H
#define TN_TCP_CONNECTION_H

#include <Common.h>
#include <memory>
#include <functional>

namespace TinyNet
{
    class TcpSocket4;
    class EventDispatcher;

    TN_API class TcpConnection
    {
    public:
        using Callback = std::function<void(TcpConnection*)>;

    public:
        static TcpConnection* create(TcpSocket4* socket);

        bool attach(TcpSocket4* socket);

        void setOnRead(Callback callback) { onRead_ = callback; }

    private:
        TcpConnection() = default;

        void handleRead();

    private:
        std::unique_ptr<TcpSocket4> socket_ = nullptr;
        Callback onRead_;

        friend class TcpServer4;
    };
}

#endif

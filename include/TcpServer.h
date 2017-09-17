#ifndef TN_TCP_SERVER_H
#define TN_TCP_SERVER_H

#include <Common.h>
#include <memory>
#include <vector>
#include <functional>

namespace TinyNet
{
    class TcpSocket4;
    class TcpConnection;
    class EventDispatcher;

    class TcpServer4 : public NonClonable
    {
    public:
        using Callback = std::function<void(TcpConnection*)>;

    public:
        static std::shared_ptr<TcpServer4> create(EventDispatcher* event_dispatcher,
                                                  const std::string& ip, uint16_t port);

        bool start();

        void handleAccept();

        void setOnRead(Callback callback) { onRead_ = callback; }

    private:
        TcpServer4() = default;

    private:
        EventDispatcher* event_dispatcher_;
        std::unique_ptr<TcpSocket4> socket_;
        std::vector<std::shared_ptr<TcpConnection>> connections_;
        Callback onRead_ = [](TcpConnection* connection) {};
    };
}

#endif

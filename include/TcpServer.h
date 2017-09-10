#ifndef TN_TCP_SERVER_H
#define TN_TCP_SERVER_H

#include <Common.h>
#include <memory>
#include <vector>

namespace TinyNet
{
    class TcpSocket4;
    class TcpConnection;
    class EventDispatcher;

    class TcpServer4 : public NonClonable
    {
    public:
        static std::shared_ptr<TcpServer4> create(EventDispatcher* event_dispatcher,
                                                  const std::string& ip, uint16_t port);

        bool start();

        void handleAccept();

    private:
        TcpServer4() = default;

    private:
        EventDispatcher* event_dispatcher_;
        std::unique_ptr<TcpSocket4> socket_;
        std::vector<std::shared_ptr<TcpConnection>> connections_;
    };
}

#endif

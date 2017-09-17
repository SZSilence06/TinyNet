#ifndef TN_TCP_CLIENT_H
#define TN_TCP_CLIENT_H

#include <Common.h>
#include <memory>
#include <functional>

namespace TinyNet
{
    class EventDispatcher;
    class TcpSocket4;
    class Sock4Addr;

    class TcpClient : public NonClonable
    {
    public:
        using Callback = std::function<void()>;

    public:
        static std::shared_ptr<TcpClient> create(EventDispatcher* event_dispatcher,
                                 const std::string& ip, uint16_t port);
        static std::shared_ptr<TcpClient> create(EventDispatcher* event_dispatcher,
                                 const Sock4Addr& addr);
        static std::shared_ptr<TcpClient> create(EventDispatcher* event_dispatcher);

        bool setNonBlock(bool nonBlock);

        bool connect(const std::string& ip, uint16_t port);
        bool connect(const Sock4Addr& server);

        void setOnConnected(Callback callback) { onConnected_ = callback; }
        void setOnRead(Callback callback) { onRead_ = callback; }

    private:
        TcpClient() = default;

        void handleConnected();
        void handleRead();
        void handleWrite();

    private:
        EventDispatcher* event_dispatcher_ = nullptr;
        std::unique_ptr<TcpSocket4> socket_ = nullptr;

        bool isNonBlock_ = false;
        bool isConnected = false;

        Callback onConnected_ = [](){};
        Callback onRead_ = [](){};
    };
}

#endif

#ifndef TN_SOCKET_H
#define TN_SOCKET_H

#include <Common.h>
#include <memory>
#include <functional>
#include <poll.h>
#include <Event.h>
#include <Addr.h>

namespace TinyNet
{
    TN_API class Socket : public NonClonable
    {
    public:
        using Callback = std::function<void()>;

    public:
        Socket() = default;
        virtual ~Socket();

        bool listen();
        bool checkConnection();
        bool setNonBlock(bool nonBlock);

        void setMaxQueueSize(int value) { max_queue_size_ = value; }

        int getFd() const { return fd_; }

        virtual std::string getIp() const = 0;
        virtual uint16_t getPort() const = 0;

        uint32_t getEvents() const { return events_;}
        void setEvents(uint32_t events) { events_ = events; }

        void setOnRead(Callback onRead) { onRead_ = onRead; }
        void setOnWrite(Callback onWrite) { onWrite_ = onWrite;}

        void handleRead() { onRead_(); }
        void handleWrite() { onWrite_(); }

    protected:
        int fd_ = -1;
        int max_queue_size_ = 20;
        uint32_t events_;
        Callback onRead_ = [](){};
        Callback onWrite_ = [](){};
    };

    TN_API class Socket4 : public Socket
    {
    public:
        virtual std::string getIp() const override;
        virtual uint16_t getPort() const override;
        Sock4Addr getAddr() const;
        Sock4Addr getPeerAddr() const;
    };

    TN_API class TcpSocket4 : public Socket4
    {
    public:
        static TcpSocket4* create(const Sock4Addr& addr);
        static TcpSocket4* create(int fd);

        bool connect(const Sock4Addr& addr);

    private:
        TcpSocket4() = default;
    };
}

#endif

#include <TcpClient.h>
#include <EventDispatcher.h>
#include <Addr.h>
#include <Socket.h>
#include <Poller.h>

namespace TinyNet
{
    std::shared_ptr<TcpClient> TcpClient::create(EventDispatcher *event_dispatcher,
                                 const std::string &ip, uint16_t port)
    {
        Sock4Addr addr(ip, port);
        return create(event_dispatcher, addr);
    }

    std::shared_ptr<TcpClient> TcpClient::create(EventDispatcher *event_dispatcher)
    {
        Ip4Addr ip = Ip4Addr::Any();
        Sock4Addr addr(ip, 0);
        return create(event_dispatcher, addr);
    }

    std::shared_ptr<TcpClient> TcpClient::create(EventDispatcher *event_dispatcher,
                                 const Sock4Addr& addr)
    {
        TcpSocket4* socket = TcpSocket4::create(addr);
        if(socket == nullptr)
            return nullptr;

        TcpClient* client = new TcpClient();
        client->event_dispatcher_ = event_dispatcher;
        client->socket_.reset(socket);

        return std::shared_ptr<TcpClient>(client);
    }

    bool TcpClient::setNonBlock(bool nonBlock)
    {
        bool result = socket_->setNonBlock(nonBlock);
        if(result)
            isNonBlock_ = nonBlock;
        return result;
    }

    bool TcpClient::connect(const std::string &ip, uint16_t port)
    {
        Sock4Addr server(ip, port);
        return connect(server);
    }

    bool TcpClient::connect(const Sock4Addr &server)
    {
        if(isNonBlock_)
        {
            socket_->setOnRead([this]() { handleRead(); });
            socket_->setOnWrite([this](){ handleConnected(); });
            event_dispatcher_->getPoller()->addSocket(socket_.get());
        }
        bool result = socket_->connect(server);
        if(isNonBlock_ && result == true)
        {
            //connected immediately
            handleConnected();
            return true;
        }
        if(result == false)
        {
            if(isNonBlock_ && errno == EINPROGRESS)
                return true;
            return false;
        }
        return result;
    }

    void TcpClient::handleConnected()
    {
        if(socket_->checkConnection() == false)
        {
            //connection failed
        }
        else
        {
            onConnected_();
            socket_->setOnWrite([this](){handleWrite();});
        }
    }

    void TcpClient::handleRead()
    {
        onRead_();
    }

    void TcpClient::handleWrite()
    {

    }
}

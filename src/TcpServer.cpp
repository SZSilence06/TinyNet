#include <TcpServer.h>
#include <Socket.h>
#include <Logger.h>
#include <Addr.h>
#include <EventDispatcher.h>
#include <Poller.h>
#include <TcpConnection.h>
#include <iostream>

namespace  TinyNet
{
    std::shared_ptr<TcpServer4> TcpServer4::create(EventDispatcher* event_dispatcher,
                                                   const std::string& ip, uint16_t port)
    {
        Sock4Addr addr(ip, port);
        TcpSocket4* socket = TcpSocket4::create(addr);
        if(socket == nullptr)
            return nullptr;

        TcpServer4* server = new TcpServer4();
        server->event_dispatcher_ = event_dispatcher;
        server->socket_.reset(socket);
        return std::shared_ptr<TcpServer4>(server);
    }

    bool TcpServer4::start()
    {
        if(socket_ == nullptr)
        {
            TN_FATAL("Try to start an invalid server!");
            return false;
        }
        if(socket_->listen() == false)
        {
            TN_ERROR("Server failed to listen!");
            return false;
        }
        socket_->setOnRead([this](){handleAccept();});
        socket_->setEvents(POLLIN);

        Poller* poller = event_dispatcher_->getPoller();
        if(poller->addSocket(socket_.get()) == false)
            return false;

        TN_INFO((std::string)"TCP server started. Listening on " + socket_->getIp() + ":"
                + std::to_string(socket_->getPort()));

        return true;
    }

    void TcpServer4::handleAccept()
    {
        struct sockaddr_in addr;
        socklen_t addr_len;
        int fd;
        if(fd = accept(socket_->getFd(), (struct sockaddr*)&addr, &addr_len) == -1)
        {
            TN_ERROR("Fail to accept connection!");
            return;
        }
        TcpSocket4* socket = TcpSocket4::create(fd);
        socket->setEvents(POLLIN | POLLOUT);

        TcpConnection* connection = TcpConnection::create(socket);
        socket->setOnRead([connection](){ connection->handleRead(); });
        if(event_dispatcher_->getPoller()->addSocket(socket) == false)
        {
            TN_ERROR("Failed to add socket to poller!");
            delete connection;
        }

        connections_.push_back(std::shared_ptr<TcpConnection>(connection));
        TN_INFO("New connection established.");
    }
}

#include <TcpConnection.h>
#include <Socket.h>
#include <EventDispatcher.h>
#include <Poller.h>
#include <Logger.h>

namespace TinyNet
{
    TcpConnection* TcpConnection::create(TcpSocket4 *socket)
    {
        TcpConnection* connection = new TcpConnection();
        connection->socket_.reset(socket);
        return connection;
    }

    void TcpConnection::handleRead()
    {
        onRead_(this);
    }
}

#include <TcpConnection.h>
#include <Socket.h>

namespace TinyNet
{
    TcpConnection* TcpConnection::create(TcpSocket4 *socket)
    {
        TcpConnection* connection = new TcpConnection();
        connection->socket_.reset(socket);
        return connection;
    }
}

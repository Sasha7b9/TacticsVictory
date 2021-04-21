// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/ConnectorTCP_.h"
#include "Network/Other/SocketsTCP_.h"
#include "Utils/StringUtils_.h"
#include <sstream>


static sockpp::socket_initializer sockInit;


BaseConnectorTCP::~BaseConnectorTCP()
{
    Release();
}


bool BaseConnectorTCP::Connect(const std::string &host, uint16 port)
{
//    static int counter = 0;

    if (!connection)
    {
        connection = std::make_unique<sockpp::tcp_connector>();
    }

    try
    {
        volatile in_addr_t addr = sockpp::inet_address().resolve_name(host);
        addr = addr;
    }
    catch(std::runtime_error &error)
    {
        LOGERRORF("%s:%d %s", host.c_str(), port, error.what());

        return false;
    }

    connection->connect({ host, port });

    if (connection->is_connected())
    {
        SetReadTimeOut(1);
        SetWriteTimeOut(1);

        LOGWRITEF("Connect to %s:%d success", host.c_str(), port);
    }
    else
    {
//        LOGERRORF("%d - Connect to %s:%d failed. Error : %s", counter++, host.c_str(), port,
//            connection->last_error_str().c_str());
    }

    return connection->is_connected();
}


void BaseConnectorTCP::SetReadTimeOut(uint timeout)
{
    connection->read_timeout((std::chrono::milliseconds)timeout);
}


void BaseConnectorTCP::SetWriteTimeOut(uint timeout)
{
    connection->write_timeout((std::chrono::milliseconds)timeout);
}


void BaseConnectorTCP::Release()
{
    Disconnect();
    connection.reset();
}


void BaseConnectorTCP::Disconnect()
{
    if (connection)
    {
        LOGWRITE("Disconnect");

        connection->close();
    }
}


void BaseConnectorTCP::Transmit(const void *data, uint size)
{
    connection->write_n(data, size);
}


ssize_t BaseConnectorTCP::Receive(void *data, uint size)
{
    fd_set set = { 1, { connection->handle() } };

#ifdef WIN32
    TIMEVAL time = { 0, 1000 };
#else
    struct timeval time = { 1, 0 };
#endif

    int ready = ::select(0, &set, 0, 0, &time);

    if (ready == 1)
    {
        return connection->read(data, size);
    }

    return 0;
}


bool BaseConnectorTCP::IsConnected() const
{
    if (!connection)
    {
        return false;
    }

    if (!connection->is_open())
    {
        return false;
    }

    if (!connection->is_connected())
    {
        return false;
    }

    return true;
}


bool AcceptorTCP::Bind(uint16 port)
{
    connection = std::make_unique<sockpp::tcp_acceptor>(port, 0);

    if (connection->is_open())
    {
        LOGWRITEF("Bind to port %d success", port);
    }
    else
    {
        LOGERRORF("Bind to port %d failed", port);
        LOGERROR(connection->last_error_str().c_str());
    }

    return connection->is_open();
}


bool AcceptorTCP::Accept(Socket &socket)
{
    socket.peer = std::make_unique<sockpp::inet_address>();

    socket.sock = connection->accept(socket.peer.get());

    if (!socket.sock)
    {
        LOGERRORF("Fail accept connection. Error : %s", connection->last_error_str().c_str());
    }
    else
    {
        LOGWRITEF("Accept connection from %s", socket.peer->to_string().c_str());
    }

    return socket.sock.is_open();
}


void AcceptorTCP::Socket::Transmit(pchar data)
{
    int size = SU::Length(data);

    sock.write(&size, sizeof(int));

    sock.write(std::string(data));
}


void AcceptorTCP::Socket::Transmit(const std::string &data)
{
    size_t size = data.size();

    sock.write(&size, sizeof(int));

    sock.write(data);
}

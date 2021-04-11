// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/SocketsTCP_.h"
#include "Utils/StringUtils_.h"


static sockpp::socket_initializer sockInit;


ConnectorTCP::~ConnectorTCP()
{
    Release();
}


bool ConnectorTCP::Connect(const std::string &host, uint16 port)
{
    static int counter = 0;

    if (!connection)
    {
        connection = std::make_unique<sockpp::tcp_connector>();
    }

    volatile in_addr_t addr = 0;

    try
    {
        addr = sockpp::inet_address().resolve_name(host);
    }
    catch(std::runtime_error &error)
    {
        LOGERRORF("%s:%d %s", host.c_str(), port, error.what());

        return false;
    }

    connection->connect({ host, port });

    if (connection->is_connected())
    {
        SetReadTimeOut(1000);
        SetWriteTimeOut(1000);

        LOGWRITEF("Connect to %s:%d success", host.c_str(), port);
    }
    else
    {
        LOGERRORF("%d - Connect to %s:%d failed. Error : %s", counter++, host.c_str(), port,
            connection->last_error_str().c_str());
    }

    return connection->is_connected();
}


void ConnectorTCP::SetReadTimeOut(uint timeout)
{
    connection->read_timeout((std::chrono::milliseconds)timeout);
}


void ConnectorTCP::SetWriteTimeOut(uint timeout)
{
    connection->write_timeout((std::chrono::milliseconds)timeout);
}


void ConnectorTCP::Release()
{
    Disconnect();
    connection.reset();
}


void ConnectorTCP::Disconnect()
{
    if (connection)
    {
        LOGWRITE("Disconnect");

        connection->close();
    }
}


void ConnectorTCP::Transmit(void *data, uint size)
{
    connection->write_n(data, size);
}


uint ConnectorTCP::Receive(void *data, uint size)
{
    return (uint)connection->read_n(data, size);
}


bool ConnectorTCP::IsConnected() const
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


std::string ConnectorTCP::Receive()
{
    uint size = 0;
    
    connection->read_n(&size, sizeof(uint));

    std::string result;
    result.resize((size_t)size);

    if (size != 0)
    {
        connection->read_n(&result[0], (size_t)size);
    }
    else
    {
        LOGWARNINGF("Not received a file from address %s, peer %s", connection->address().to_string().c_str(),
            connection->peer_address().to_string().c_str());
    }

    return result;
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

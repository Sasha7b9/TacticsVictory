// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/SocketsTCP_.h"


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

    connection->connect({ host, port });

    if (connection->is_connected())
    {
        LOGWRITEF("Connect to %s:%d success", host.c_str(), port);
    }
    else
    {
        LOGERRORF("%d - Connect to %s:%d failed. Error : %s", counter++, host.c_str(), port,
            connection->last_error_str().c_str());
    }

    return connection->is_connected();
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
        connection->close();
    }
}


void ConnectorTCP::SetReadTimeOut(uint timeOutMS)
{
    connection->read_timeout(std::chrono::milliseconds(timeOutMS));
}


void ConnectorTCP::Transmit(pchar data)
{
    int size = SU::Length(data);

    connection->write(&size, sizeof(int));

    connection->write(data);
}


void ConnectorTCP::Transmit(const std::string &data)
{
    Transmit(data.c_str());
}


void ConnectorTCP::Receive(std::string &data)
{
    uint size = 0;

    connection->read_n(&size, sizeof(uint));

    data.resize(size); //-V106

    if (size != 0)
    {
        connection->read_n(&data[0], size); //-V106
    }
    else
    {
        LOGWARNINGF("Not received a file from peer %s", connection->peer_address().to_string().c_str());
    }
}


std::string ConnectorTCP::Receive()
{
    uint size = 0;
    
    connection->read_n(&size, sizeof(uint));

    std::string result;
    result.resize((size_t)size); //-V2533 //-V201

    if (size != 0)
    {
        connection->read_n(&result[0], (size_t)size); //-V2533 //-V201
    }
    else
    {
        LOGWARNINGF("Not received a file from address %s, peer %s", connection->address().to_string().c_str(),
            connection->peer_address().to_string().c_str());
    }

    return result;
}


std::string ConnectorTCP::ReceiveWait()
{
    std::string result;

    while (result.size() == 0)
    {
        Receive(result);
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


void ThreadSocket(AcceptorTCP::Socket socket, void (*onReceive)(AcceptorTCP::Socket &, pchar, int))
{
    while (socket.sock.is_open())
    {
        static const int MAX_RECEIVED = 512;

        char received[MAX_RECEIVED];

        ssize_t n = socket.sock.read(received, MAX_RECEIVED);

        if (n <= 0)
        {
            LOGWRITEF("Close connection %s", socket.peer->to_string().c_str());
            break;
        }

        onReceive(socket, received, static_cast<int>(n));
    }
}


void AcceptorTCP::Socket::Run(void(*onReceive)(AcceptorTCP::Socket &socket, pchar symbols, int numSymbols))
{
    std::thread thread(ThreadSocket, std::move(*this), onReceive);
    thread.detach();
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
 

std::pair<std::string, uint16> ConnectorTCP::ParseAddress(pchar fullAddressIn)
{
    std::pair<std::string, uint16> result;

    if (fullAddressIn == nullptr || *fullAddressIn == '\0')
    {
        result.first = "";
        result.second = 0;
        return result;
    }

    pchar pointer = fullAddressIn;

    while (*pointer != ':')
    {
        result.first.push_back(*pointer);
        ++pointer;
    }

    result.second = static_cast<uint16>(atoi(pointer + 1)); //-V2508

    return result;
}

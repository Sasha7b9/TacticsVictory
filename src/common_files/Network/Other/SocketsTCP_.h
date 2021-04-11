// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


// Клиент клиента
class ConnectorTCP
{
public:

    virtual ~ConnectorTCP();

    void Release();

    bool Connect(const std::string &host, uint16 port);

    void SetReadTimeOut(uint timeout);

    void SetWriteTimeOut(uint timeout);

    void Disconnect();

    bool IsConnected() const;

    // Передаёт size байт из массива data
    void Transmit(const void *data, uint size);

    // Делает попытку приёма size байт в массив data. Возвращает количество реально принятых байт.
    // В случае ошибки возрващает -1
    // Если size == 0, то ничего не читает, а возвращает количество доступных для чтения байт
    ssize_t Receive(void *data, uint size, int flags = 0);

private:

    std::unique_ptr<sockpp::tcp_connector>  connection;
};


// Сервер
class AcceptorTCP
{
public:

    struct Socket
    {
        std::unique_ptr<sockpp::inet_address>  peer;            // Здесь хранится адрес подключённого клиента
        sockpp::tcp_socket sock;
        void Transmit(pchar string);
        void Transmit(const std::string &data);
    };

public:

    bool Bind(uint16 port);

    bool Accept(Socket &socket);

private:

    std::unique_ptr<sockpp::tcp_acceptor> connection;

    struct CompareSocket
    {
        bool operator()(const sockpp::tcp_socket *lhs, const sockpp::tcp_socket *rhs) const
        {
            return lhs->peer_address().address() < rhs->peer_address().address();
        }
    };

    std::map<sockpp::tcp_socket *, sockpp::inet_address, CompareSocket> sockets;
};

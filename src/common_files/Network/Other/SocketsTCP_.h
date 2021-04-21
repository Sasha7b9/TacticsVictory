// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include <memory>
#include <map>





// ������
class AcceptorTCP
{
public:

    struct Socket
    {
        std::unique_ptr<sockpp::inet_address>  peer;            // ����� �������� ����� ������������� �������
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

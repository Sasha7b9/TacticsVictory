// 2021/04/18 23:24:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct TypeServer
{
    enum E
    {
        TCP,
        UDP
    };
};


class SocketConfig
{
public:

    SocketConfig() {};

    virtual ~SocketConfig() = default;

    uint16        port = 8080;
    int           backLog = 1024;
    TypeServer::E type = TypeServer::UDP;
    std::string   ip = "127.0.0.1";
};


class SocketUtility
{
public:

    inline static SocketUtility &GetInstance();

    int BindSocket(const SocketConfig &config);

    bool CloseSocket(int &sock_fd);

private:

    SocketUtility() = default;
    virtual ~SocketUtility() = default;

    int InitSocket(TypeServer::E type);
};


class ServerUDP
{

};

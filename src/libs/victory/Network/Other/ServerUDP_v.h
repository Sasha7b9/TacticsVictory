// 2021/04/18 23:24:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include <memory>
#include <string>
#include <thread>


class ThreadUDP;


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
public:
    ServerUDP();
    virtual ~ServerUDP();

    bool Init(const SocketConfig &config, int network_size);

private:

    void StartThreadUDP(int index);

    SocketConfig config;
    std::vector<std::unique_ptr<ThreadUDP>> threadsUPD;
    std::vector<std::thread> threads;
    int sock_fd = 0;
    static const int network_capacity = 128;
};

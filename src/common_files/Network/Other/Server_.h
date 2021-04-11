// 2021/04/09 14:45:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct ServerInfo;


struct SocketAddress
{
    std::string ToString()
    {
        char buffer[100];

        sprintf_s(buffer, 100, "%d.%d.%d.%d:%d", sin.sin_addr.S_un.S_un_b.s_b1,
            sin.sin_addr.S_un.S_un_b.s_b2,
            sin.sin_addr.S_un.S_un_b.s_b3,
            sin.sin_addr.S_un.S_un_b.s_b4,
            sin.sin_port);

        return std::string(buffer);
    };

    sockaddr_in sin;
};


struct ClientInfo
{
    SocketAddress      address;
    std::vector<uint8> data;
    void *buffer;
};


class Server
{
public:

    void Run();

    void Stop() { run = false; }

    void AppendHandler(pchar command, pFuncVpV handler);

    void Prepare();

    void SendString(void *bev, pchar message);

    static std::map<std::string, pFuncVpV> handlers;    // Здесь хранятся обработчики запросов по первому слову

    static std::vector<std::string> words;              // Используется в обработчиках

private:

    bool run = true;
};

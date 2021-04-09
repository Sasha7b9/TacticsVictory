// 2021/04/09 14:45:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/SocketsTCP_.h"


struct ServerInfo;


class Server
{
public:

    void Run();

    void Stop() { run = false; }

    void AppendHandler(pchar command, pFuncVV handler);

    void AppendServerInfo(const ServerInfo &info);

    void Prepare();

    static void HandlerReceivedSocket(AcceptorTCP::Socket &socket, pchar symbols, int number);

    static std::map<std::string, pFuncVV> map;    // ����� �������� ����������� �������� �� ������� �����

    static std::map<std::string, ServerInfo> livingrooms;   // ����� �������� ���������� � ������������ ��������

private:

    bool run = true;
};

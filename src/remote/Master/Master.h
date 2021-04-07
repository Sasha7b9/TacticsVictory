// Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/NetworkTypes_.h"
#include "Network/Other/SocketsTCP_.h"


class Master
{
public:

    int Run();

    static void Terminate();

    static std::map<std::string, ServerInfo> servers;

private:

    static void Prepare();

    static void HandlerReceivedSocket(AcceptorTCP::Socket &socket, pchar data, int size);

    // Мастер работает, пока run == true
    static bool run;
};

// Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/SocketsTCP_.h"


class Master
{
public:

    int Run();

private:

    static void HandlerReceivedSocket(AcceptorTCP::Socket &socket, pchar data, int size);

    // Мастер работает, пока run == true
    static bool run;
};

// Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Network/Other/Server_.h"
#include "Network/Other/SocketsTCP_.h"


/*
    - Прочитать из файла конфигурации адрес порта, к которому нужно подключиться - "port"
    - Подключиться к данному порту на прослушивание и обрабатывать комнады:
*/


static bool run = true;

extern void HandlerReceivedSocket(AcceptorTCP::Socket &socket, pchar data, int size);


int main(int, char *[])
{
    setlocale(LC_ALL, "Russian");

    LogRAW::Create("Master.log", false);

    LOGWRITE("Start Master");

    if (!TheConfig.Load("Master.conf"))
    {
        return -1;
    }

    TheServer.Run();

    return 0;
}



void HandlerTerminate()
{
    run = false;
}

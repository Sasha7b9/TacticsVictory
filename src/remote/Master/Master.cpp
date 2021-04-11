// Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Network/Other/Server_.h"


/*
    - Прочитать из файла конфигурации адрес порта, к которому нужно подключиться - "port"
    - Подключиться к данному порту на прослушивание и обрабатывать комнады:
*/


int main(int, char *[])
{
    setlocale(LC_ALL, "Russian");

    LogRAW::Create("Master.log", false);

    LOGWRITE("Start Master");

    if (!TheConfig.Load("Master.conf"))
    {
        return -1;
    }

    TheSettings.Load("Settings.conf");

    TheServer.Prepare();

    TheServer.Run((uint16)TheSettings.GetInt("master_server", "port"));

    return 0;
}

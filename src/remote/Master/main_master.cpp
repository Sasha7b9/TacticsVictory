// Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_v.h"
#include "Network/Other/ServerTCP_v.h"
#include <locale>

/*
    - Прочитать из файла конфигурации адрес порта, к которому нужно подключиться - "port"
    - Подключиться к данному порту на прослушивание и обрабатывать комнады:
*/

int main(int, char *[])
{
    setlocale(LC_ALL, "Russian");

    LogRAW::Create("Master.log", false);

    LOGWRITE("Start Master");
    LOGWARNING("Test Warning");
//    int i = 10;
//    LOGWARNINGF("Test Warning %d", i);

    if (!TheConfig.Load("Master.conf"))
    {
        return -1;
    }

    TheSettings.Load("Settings.conf");

    extern void PrepareServerTCP();

    PrepareServerTCP();

    TheServer.Run((uint16)TheSettings.GetInt("master_server", "port"));

    return 0;
}


std::string LogRAW::NameApplication()
{
    return "Master";
}

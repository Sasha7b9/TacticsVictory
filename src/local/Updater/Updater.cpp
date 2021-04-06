// 2021/04/02 17:14:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");

    LogRAW::Create("Updater.log", false);

    LOGWRITE("Start Updater");

    if (argc != 2)
    {
        LOGERROR("No address master server specified.");
        LOGERROR("Define it: Updater.exe 127.0.0.1:40000");

        return -1;
    }

    TheMasterServer.Connect(argv[1]);

    TheMasterServer.Destroy();

    LOGWRITE("Exit Updater");

    return 0;
}

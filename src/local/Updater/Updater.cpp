// 2021/04/02 17:14:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return -1;
    }

    setlocale(LC_ALL, "Russian");

    LogRAW::Create("Updater.log");

    LOGWRITE("Start Updater");

    TheMaster.Connect(argv[1]);

    TheMaster.Destroy();

    return 0;
}

// 2021/04/02 17:14:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"


int main()
{
    setlocale(LC_ALL, "Russian");

    LogRAW::Create("Monitor.log", false);

    LOGWRITE("Start Monitor");

    TheConfig.Load("Monitor.cfg");

//    TheMasterServer.Connect(TheConfig.GetString("address master"));

    return 0;
}

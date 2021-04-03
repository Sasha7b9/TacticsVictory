// 2021/04/02 17:14:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


int main()
{
    setlocale(LC_ALL, "Russian");

    LogRAW::Create("Monitor.log");

    LOGWRITE("Start Monitor");

    TheConfig.Load("Monitor.cfg");

    TheMaster.Connect(TheConfig.GetStringValue("address master"));

    return 0;
}

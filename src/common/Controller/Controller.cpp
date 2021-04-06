// 2021/04/02 17:14:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


int main()
{
    setlocale(LC_ALL, "Russian");

    LogRAW::Create("Controller.log", false);

    LOGWRITE("Start Controller");

    TheConfig.Load("Contoller.cfg");

//    TheMasterServer.Connect(TheConfig.GetString("address master"));

    return 0;
}

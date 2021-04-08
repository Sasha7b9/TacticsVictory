// 2021/04/02 17:14:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


int main()
{
    setlocale(LC_ALL, "Russian");

    LogRAW::Create("LivingRoom.log", false);

    LOGWRITE("Start LivingRoom");

    TheConfig.Load("LivingRoom.cfg");

//    TheMasterServer.Connect(TheConfig.GetString("address master"));

    return 0;
}

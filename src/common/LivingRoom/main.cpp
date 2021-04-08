// 2021/04/02 17:14:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "LivingRoom.h"


int main(int args, char *argv[])
{
    setlocale(LC_ALL, "Russian");

    LogRAW::Create("LivingRoom.log", false);

    LOGWRITE("Start LivingRoom");

    if (args < 2)
    {
        LOGERRORF("Not specified address master server");
        return -1;
    }

    if (TheConfig.Load("LivingRoom.conf"))
    {
        return LivingRoom().Run();
    }

    return 0;
}
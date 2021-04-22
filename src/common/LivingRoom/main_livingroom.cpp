// 2021/04/02 17:14:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "LivingRoom.h"
#include "FileSystem/ConfigurationFile_.h"


int main(int args, char *argv[])
{
    setlocale(LC_ALL, "Russian");

    LogRAW::Create("LivingRoom.log", false);

    LOGWRITE("Start LivingRoom");

    if (TheSettings.Load("Settings.conf"))
    {
        return TheLivingRoom.Run(args < 2 ? nullptr : argv[1]);
    }

    return 0;
}
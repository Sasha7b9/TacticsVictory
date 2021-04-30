// 2021/04/02 17:14:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "LivingRoom.h"
#include "FileSystem/ConfigurationFile_v.h"


int main(int , char *[])
{
    setlocale(LC_ALL, "Russian");

    LogRAW::Create("LivingRoom.log", false);

    LOGWRITE("Start LivingRoom");

    if (TheSettings.Load("Settings.conf"))
    {
        return TheLivingRoom.Run(TheSettings.GetString("master_server", "host"));
    }

    return 0;
}

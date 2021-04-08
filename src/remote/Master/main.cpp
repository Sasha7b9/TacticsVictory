// Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


int main(int, char *[])
{
    setlocale(LC_ALL, "Russian");

    LogRAW::Create("Master.log", false);

    LOGWRITE("Start Master");

    if (TheConfig.Load("Master.conf"))
    {
        return Master().Run();
    }

    return -1;
}

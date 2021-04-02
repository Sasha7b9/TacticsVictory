// Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


int main(int, char *[]) //-V2504
{
    setlocale(LC_ALL, "Russian");

    LogRAW::Create("Master.log");

    LOGWRITE("Start Master");

    int result = -1;

    if (TheConfig.Load("Master.conf"))
    {
        result = Master().Run();
    }

    return result;
}

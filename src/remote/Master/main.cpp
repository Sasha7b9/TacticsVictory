#include "stdafx.h"


int main(int, char *[]) //-V2504
{
    setlocale(LC_ALL, "Russian");

    Log::Create("Master.log");

    LOGWRITE("Start Master");

    if (!TheConfig.Load("Master.conf"))
    {
        return -1;
    }

    return Master().Run();
}
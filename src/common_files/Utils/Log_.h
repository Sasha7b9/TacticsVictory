// 2021/03/30 21:23:50 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


#ifdef LOG_U3D

#include "Utils/LogU3D_.h"

#else

#include "Utils/LogRAW_.h"

#endif


struct ConsoleLog
{
    static void Create();

    static void Write(pchar message);

    static void Destroy();

#ifdef WIN32
    static HANDLE handle;
#endif
};

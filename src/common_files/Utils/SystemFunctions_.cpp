// 2021/02/27 23:59:34 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Utils/SystemFunctions_.h"
#include "Utils/SystemUtils_.h"


#ifdef WIN32

void win::SetConsoleCP(uint cp)
{
    if (!::SetConsoleCP(cp))
    {
        DISPLAY_LAST_ERROR();
    }
}

#endif

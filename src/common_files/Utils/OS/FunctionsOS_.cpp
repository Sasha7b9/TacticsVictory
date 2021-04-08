// 2021/02/27 23:59:34 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Utils/OS/FunctionsOS_.h"
#include "Utils/OS/UtilsOS_.h"


#ifdef WIN32

void win::SetConsoleCP(uint cp)
{
    if (!::SetConsoleCP(cp))
    {
        DISPLAY_LAST_ERROR();
    }
}

#endif

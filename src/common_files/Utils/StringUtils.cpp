// 2021/02/27 23:01:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Utils/StringUtils.h"


char *SU::Strcat(char *dest, pchar source)
{
#ifdef WIN32
#pragma warning(push, 2)
#endif
    return strcat(dest, source);
#ifdef WIN32
#pragma warning(pop)
#endif
}

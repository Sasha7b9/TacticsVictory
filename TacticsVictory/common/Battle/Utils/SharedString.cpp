// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "SharedString.h"


using namespace Pi;


SharedString::SharedString(char *text) : Shared()
{
    size_t length = strlen(text) + 1;
    buffer = new char[length];
    strcpy(buffer, text);
}

SharedString::~SharedString()
{
    SAFE_DELETE(buffer);
}

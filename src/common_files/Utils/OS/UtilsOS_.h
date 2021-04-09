// 2021/02/27 23:59:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


#define DISPLAY_LAST_ERROR() System::DisplayLastError(__FILE__, __LINE__)


namespace System
{
    void DisplayLastError(const char *file, int line);
}


namespace win
{
    void SetConsoleCP(uint);
}

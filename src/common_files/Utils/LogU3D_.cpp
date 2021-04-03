// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Utils/Log_.h"
#include "Utils/SystemFunctions_.h"
#include "Utils/SystemUtils_.h"


bool LogU3D::enabledExtendedInfo = false;

#ifdef WIN32
HANDLE ConsoleLog::handle = nullptr;
#endif


LogU3D::LogU3D(LogU3D **self) : Log(TheContext)
{
    ConsoleLog::Create();

    *self = this;
}


LogU3D::~LogU3D()
{
    ConsoleLog::Destroy();
}


void LogU3D::Write(int level, const String &message, pchar file, pchar func, int numLine)
{
    String str = message;
    if (enabledExtendedInfo)
    {
        while (str.Length() < 80)
        {
            str += "..........";
        }
        while (str.Length() < 90)
        {
            str += ".";
        }

        str += String(file) + String(":") + String(func) + String(":") + String(numLine);
    }

    Log::Write(level, str);

    ConsoleLog::Write(str.CString());
}


void LogU3D::EnableExtendedInfo()
{
    enabledExtendedInfo = true;
}


void LogU3D::DisableExtendedInfo()
{
    enabledExtendedInfo = false;
}


void ConsoleLog::Create()
{
#ifdef WIN32

    FreeConsole();

    if (GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE)
    {
        /*
        *  Чтобы в консоли не выводились кракозяблы вместо русских букв, нужно устанавливать шрифт Lucida Console
        */

//        win::SetConsoleCP(1251);

//        if (!SetConsoleOutputCP(1251))
//        {
//            DISPLAY_LAST_ERROR();
//        }

        if (!AllocConsole())
        {
            DISPLAY_LAST_ERROR();
        }

        win::SetConsoleCP(1251);

        if (!SetConsoleOutputCP(1251))
        {
            DISPLAY_LAST_ERROR();
        }

        handle = GetStdHandle(STD_OUTPUT_HANDLE);

        if (handle == INVALID_HANDLE_VALUE)
        {
            DISPLAY_LAST_ERROR();
        }

        RECT rect;

        HWND hwnd = GetConsoleWindow();

        if (!GetWindowRect(hwnd, &rect))
        {
            DISPLAY_LAST_ERROR();
        }

        if (!MoveWindow(hwnd, 0, 0, rect.right - rect.left, rect.bottom - rect.top, true))
        {
            DISPLAY_LAST_ERROR();
        }
    }

#endif
}


void ConsoleLog::Destroy()
{
#ifdef WIN32
    FreeConsole();
#endif
}


void ConsoleLog::Write(pchar message)
{
#ifdef WIN32

    if (handle)
    {
        if (!WriteConsoleA(handle, (void *)message, (DWORD)std::strlen(message), NULL, NULL))
        {
            DISPLAY_LAST_ERROR();
        }

        if (!WriteConsoleA(handle, "\n", 1, NULL, NULL))
        {
            DISPLAY_LAST_ERROR();
        }
    }
    else

#endif

    {
        std::cout << message << "\n";
    }
}

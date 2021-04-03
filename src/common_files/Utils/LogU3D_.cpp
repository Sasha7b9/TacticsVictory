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

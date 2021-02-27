// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Utils/Log_.h"


bool LogT::enabledExtendedInfo = false;


LogT::LogT(Context *context) : Log(context)
{

}


void LogT::Write(int level, const String &message, pchar file, pchar func, int numLine)
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
}


void LogT::EnableExtendedInfo()
{
    enabledExtendedInfo = true;
}


void LogT::DisableExtendedInfo()
{
    enabledExtendedInfo = false;
}

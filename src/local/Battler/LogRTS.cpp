// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "LogRTS.h"
#include "GUI/Windows/Console.h"


bool LogRTS::enabledExtendedInfo = false;


LogRTS::LogRTS(Context *context) : Log(context)
{

}


void LogRTS::Write(int level, const String &message, char *file, char *func, int numLine)
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
    TheConsole->Write(str);
}


void LogRTS::EnableExtendedInfo()
{
    enabledExtendedInfo = true;
}


void LogRTS::DisableExtendedInfo()
{
    enabledExtendedInfo = false;
}

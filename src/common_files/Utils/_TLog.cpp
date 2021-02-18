// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Utils/_TLog.h"


bool TLog::enabledExtendedInfo = false;


TLog::TLog(Context *context) : Log(context)
{

}


void TLog::Write(int level, const String &message, char *file, char *func, int numLine)
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


void TLog::EnableExtendedInfo()
{
    enabledExtendedInfo = true;
}


void TLog::DisableExtendedInfo()
{
    enabledExtendedInfo = false;
}

// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Utils/Log_.h"


bool TLog::enabledExtendedInfo = false;


TLog::TLog(Context *context) : Log(context)
{

}


void TLog::Write(int level, const String &message, pchar file, pchar func, int numLine)
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

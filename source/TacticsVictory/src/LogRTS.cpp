#include "stdafx.h"
#include "LogRTS.h"
#include "GUI/Windows/Console.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LogRTS::LogRTS(Context *context) : Log(context)
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void LogRTS::Write(int level, const String &message, char *file, char *func, int numLine)
{
    String str = message;
    if(message.Length() > 75)
    {
        str += "\n                            ";
    }
    str += String("...........................................") + String(file) + String(":") + String(func) + String(":") + String(numLine);
    Log::Write(level, str);
    gConsole->Write(str);
}

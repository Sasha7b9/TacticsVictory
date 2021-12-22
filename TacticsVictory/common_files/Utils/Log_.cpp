// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Utils/Log_.h"


using namespace Pi;

#ifndef PiLINUX
#pragma warning(push)
#pragma warning(disable:4996)
#endif


FlagLog::B      Log::flags     = 0;
DirectionLog::B Log::direction = 0;
File           *Log::file = nullptr;

#ifdef WIN32

    HANDLE          Log::handleConsole = nullptr;

#endif


void Log::Construct(FlagLog::B _flags, DirectionLog::B _direction)
{
    flags = _flags;
    direction = _direction;

    if (direction & DirectionLog::SystemConsole)
    {
#ifdef WIN32

        AllocConsole();
        handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);

#endif
    }

    if(direction & DirectionLog::File)
    {
        file = new File();
        file->Open(TheResourceMgr->GetSystemCatalog()->GetLogPath() + Engine::nameApplication + ".log", FileOpenMode::Create);
    }
}


void Log::Destruct()
{
    if(direction & DirectionLog::SystemConsole)
    {
    }

    if (direction & DirectionLog::File)
    {
        file->Close();

        delete file;
    }
}


void Log::Write(pchar format, ...)
{
    if((flags & FlagLog::Raw) == 0)
    {
        return;
    }

    static char buffer[8 * 1024];

    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

    WriteMessage(buffer);
}


void Log::WriteTrace(pchar name_file, int num_line, pchar format, ...)
{
    if ((flags & FlagLog::Raw) == 0)
    {
        return;
    }

    static char buffer[8 * 1024];

    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

    sprintf(&buffer[strlen(buffer)], "%s - \t\t\t\t%s:%d", buffer, name_file, num_line);

    WriteMessage(buffer);
}


void Log::Warning(pchar format, ...)
{
    if ((flags & FlagLog::Warning) == 0)
    {
        return;
    }

    static char buffer[4096];
    strcpy(buffer, "!!! WARNING !!! ");

    va_list args;
    va_start(args, format);
    vsprintf(&buffer[strlen(buffer)], format, args);
    va_end(args);

    WriteMessage(buffer);
}


void Log::WarningTrace(pchar name_file, int num_line, pchar format, ...)
{
    if ((flags & FlagLog::Warning) == 0)
    {
        return;
    }

    static char buffer[8 * 1024];
    strcpy(buffer, "!!! WARNING !!! ");

    va_list args;
    va_start(args, format);
    vsprintf(&buffer[strlen(buffer)], format, args);
    va_end(args);

    sprintf(&buffer[strlen(buffer)], "%s - \t\t\t\t%s:%d", buffer, name_file, num_line);

    WriteMessage(buffer);
}


void Log::Error(pchar format, ...)
{
    if ((flags & FlagLog::Error) == 0)
    {
        return;
    }

    static char buffer[4096];
    strcpy(buffer, "!!! ERROR !!! ");

    va_list args;
    va_start(args, format);
    vsprintf(&buffer[strlen(buffer)], format, args);
    va_end(args);

    WriteMessage(buffer);
}


void Log::ErrorTrace(pchar name_file, int num_line, pchar format, ...)
{
    if ((flags & FlagLog::Error) == 0)
    {
        return;
    }

    static char buffer[8 * 1024];
    strcpy(buffer, "!!! ERROR !!! ");

    va_list args;
    va_start(args, format);
    vsprintf(&buffer[strlen(buffer)], format, args);
    va_end(args);

    sprintf(&buffer[strlen(buffer)], "%s - \t\t\t\t%s:%d", buffer, name_file, num_line);

    WriteMessage(buffer);
}


void Log::WriteMessage(pchar message)
{
    if(direction & DirectionLog::EngineReport)
    {
        TheEngine->Report(message);
    }

    if (direction & DirectionLog::File)
    {
        file->WriteString(message);
    }

    if (direction & DirectionLog::SystemConsole)
    {
#ifdef WIN32

        strcat_s((char *)message, 1024, "\n");
        DWORD size;
        WriteConsoleA(handleConsole, (char *)message, static_cast<DWORD>(strlen(message)), &size, nullptr);

#else

        puts(message);

#endif
    }
}


#ifndef PiLINUX
#pragma warning(pop)
#endif

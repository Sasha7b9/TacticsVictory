// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/FileSystem_v.h"
#include "Utils/StringUtils_v.h"
#include "Utils/UtilsOS_v.h"
#include <cstdarg>
#include <iostream>
#include <mutex>


#ifdef WIN32
#pragma warning(push)
#pragma warning(disable: 4996)  // warning C4996: 'strcat': This function or variable may be unsafe. Consider using strcat_s instead.
#endif


static const int numSymbolsForMarker = 40;          // Количество сиволов под позицию ошибки

static pchar STR_ERROR = "*ERROR*";
static pchar STR_WARNING = "*WARNING*";

static FS::File *outFile;

#ifdef WIN32
HANDLE ConsoleLog::handle = nullptr;
#define END_LINE "\x0d\x0a"
#else
#define END_LINE "\n"
#endif


// Оставляет от имени файла не более определённого количества символов
static pchar ExtractName(pchar fullName)
{
    const int max = 15;

    pchar pointer = fullName + SU::Length(fullName) - 1;

    int numSlash = 0;

    int length = 1;

    while (numSlash < 2 && length < max)
    {
        if (*pointer == '\\' || *pointer == '/')
        {
            numSlash++;
        }

        pointer--;
        length++;

        if (length == max)
        {
            break;
        }
    }

    return pointer + 2;
}


void LogRAW::Create(pchar nameLog, bool new_console)
{
    outFile = new FS::File();

    if (new_console)
    {
        ConsoleLog::Create();
    }

    outFile->Create((std::string("log") + FS::delimiter + nameLog).c_str());
}

void LogRAW::Destroy()
{
    ConsoleLog::Destroy();

    delete outFile;
}


void LogRAW::ErrorF(pchar file, int line, pchar format, ...)
{
    std::vector<char> v(1024);

    CommonWriteF(file, line, v, STR_ERROR);

    std::va_list args;
    va_start(args, format);

    std::vsnprintf(v.data() + SU::Length(v.data()), v.size(), format, args);

    va_end(args);

    Write(v.data());
}


void LogRAW::WarningF(pchar file, int line, pchar format, ...)
{
    std::vector<char> v(1024);

    CommonWriteF(file, line, v, STR_WARNING);

    std::va_list args;
    va_start(args, format);

    std::vsnprintf(v.data() + SU::Length(v.data()), v.size(), format, args);

    va_end(args);

    Write(v.data());
}


void LogRAW::WriteF(pchar file, int line, pchar format, ...)
{
    std::vector<char> v(1024);

    CommonWriteF(file, line, v, "");

    std::va_list args;
    va_start(args, format);

    std::vsnprintf(v.data() + SU::Length(v.data()) , v.size(), format, args);

    va_end(args);

    Write(v.data());
}


void LogRAW::Write(pchar file, int line, pchar text)
{
    CommonWrite(file, line, text, "");
}


void LogRAW::Warning(pchar file, int line, pchar text)
{
    CommonWrite(file, line, text, STR_WARNING);
}


void LogRAW::Error(pchar file, int line, pchar text)
{
    CommonWrite(file, line, text, STR_ERROR);
}


void LogRAW::CommonWrite(pchar file, int line, pchar text, pchar symbols)
{
    std::vector<char> v(1024);

    std::string name = NameApplication();

    snprintf(v.data(), 1024, "%s | ", name.c_str());

    file = ExtractName(file);

    snprintf(v.data() + std::strlen(v.data()), 1024, "%s:%d ", file, line);

    if (symbols[0] == '\0')
    {
        while (SU::Length(v.data()) < numSymbolsForMarker - SU::Length(symbols) - 1)
        {
            std::strcat(v.data(), " ");
        }

        snprintf(v.data() + std::strlen(v.data()), 1024, "| %s", text);
    }
    else
    {
        while (SU::Length(v.data()) < numSymbolsForMarker - SU::Length(symbols) - 2)
        {
            std::strcat(v.data(), " ");
        }

        snprintf(v.data() + std::strlen(v.data()), 1024, "%s | %s", symbols, text);
    }

    Write(v.data());
}


void LogRAW::CommonWriteF(pchar file, int line, std::vector<char> &v, pchar symbols)
{
    snprintf(v.data(), 1024, "%s | ", NameApplication().c_str());

    file = ExtractName(file);

    snprintf(v.data() + std::strlen(v.data()), 1024, "%s:%d ", file, line);

    while (SU::Length(v.data()) < numSymbolsForMarker - SU::Length(symbols) - 2)
    {
        strcat(v.data(), " ");
    }

    std::strcat(v.data(), symbols);
    std::strcat(v.data(), " | ");
}


void LogRAW::Write(pchar text)
{
    static std::mutex mutex;

    mutex.lock();

    if (outFile->IsOpened())
    {
        *outFile << text << END_LINE;
    }

    ConsoleLog::Write(text);

    mutex.unlock();
}


LogRAW::~LogRAW()
{
    LOGWRITE("Close application");
}

#ifdef WIN32
#pragma warning(pop)
#endif


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

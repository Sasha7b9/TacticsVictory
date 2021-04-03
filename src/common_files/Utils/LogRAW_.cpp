// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/FileSystem_.h"
#include "Utils/StringUtils_.h"
#include "Utils/SystemFunctions_.h"
#include "Utils/SystemUtils_.h"


#ifdef WIN32
#pragma warning(push)
#pragma warning(disable: 4996)  // warning C4996: 'strcat': This function or variable may be unsafe. Consider using strcat_s instead.
#endif


static const int numSymbolsForMarker = 40;          // ���������� ������� ��� ������� ������

static pchar STR_ERROR = "*ERROR*";
static pchar STR_WARNING = "*WARNING*";

static FS::File *outFile;

#ifdef WIN32
HANDLE ConsoleLog::handle = nullptr;
#define END_LINE "\x0d\x0a"
#else
#define END_LINE "\n"
#endif


static pchar ExtractName(pchar fullName, int max)
{
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
    }

    return pointer + (length < max ? 2 : 6);
}


void LogRAW::Create(pchar nameLog)
{
    outFile = new FS::File();

#ifdef DEBUG
    ConsoleLog::Create();
#else
#ifdef WIN32
    FreeConsole();
#endif
#endif

    outFile->Create((std::string("log") + FS::delimiter + nameLog).c_str());
}

void LogRAW::Destroy()
{
    ConsoleLog::Destroy();

    delete outFile;
}


void LogRAW::ErrorF(pchar file, int line, pchar format, ...)
{
    file = ExtractName(file, numSymbolsForMarker - SU::Length(STR_ERROR) - 1);

    std::va_list args;
    va_start(args, format);

    std::vector<char> v(1024);

    snprintf(const_cast<char *const>(v.data()), 1024, "%s:%d ", file, line);

    while (SU::Length(v.data())  < numSymbolsForMarker - SU::Length(STR_ERROR) - 1)
    {
        strcat(v.data(), " ");
    }

    std::strcat(v.data(), STR_ERROR);
    std::strcat(v.data(), " | ");

    std::vsnprintf(v.data() + SU::Length(v.data()), v.size(), format, args);

    va_end(args);

    if (outFile->IsOpened())
    {
        *outFile << v.data() << END_LINE;
    }

#ifdef DEBUG

    ConsoleLog::Write(v.data());

#endif
}


void LogRAW::Error(pchar /*file*/, int /*line*/, pchar /*text*/)
{

}


void LogRAW::WarningF(pchar file, int line, pchar format, ...)
{
    file = ExtractName(file, numSymbolsForMarker - SU::Length(STR_WARNING) - 1);

    std::va_list args;
    va_start(args, format);

    std::vector<char> v(1024);

    snprintf(const_cast<char *const>(v.data()), 1024, "%s:%d ", file, line);

    while (SU::Length(v.data()) < numSymbolsForMarker - SU::Length(STR_WARNING) - 1)
    {
        std::strcat(v.data(), " ");
    }

    std::strcat(v.data(), STR_WARNING);
    std::strcat(v.data(), " | ");

    std::vsnprintf(v.data() + SU::Length(v.data()), v.size(), format, args);

    va_end(args);

    if (outFile->IsOpened())
    {
        *outFile << v.data() << END_LINE;
    }

#ifdef DEBUG

    ConsoleLog::Write(v.data());

#endif 
}


void LogRAW::WriteF(pchar file, int line, pchar format, ...)
{
    static std::mutex mutex;

    mutex.lock();

    file = ExtractName(file, numSymbolsForMarker);

    std::va_list args;
    va_start(args, format);

    std::vector<char> v(1024);

    snprintf(const_cast<char *const>(v.data()), 1024, "%s:%d ", file, line);

    while (SU::Length(v.data()) < numSymbolsForMarker)
    {
        std::strcat(v.data(), " ");
    }

    std::strcat(v.data(), "| ");

    std::vsnprintf(v.data() + SU::Length(v.data()) , v.size(), format, args);

    va_end(args);

    Write(v.data());
}


void LogRAW::Write(pchar file, int line, pchar text)
{
    file = ExtractName(file, numSymbolsForMarker);

    std::vector<char> v(1024);

    snprintf(const_cast<char *const>(v.data()), 1024, "%s:%d ", file, line);

    while (SU::Length(v.data()) < numSymbolsForMarker)
    {
        std::strcat(v.data(), " ");
    }

    std::strcat(v.data(), "| ");

    std::strcat(v.data(), text);

    Write(v.data());
}


void LogRAW::Write(pchar text)
{
    static std::mutex mutex;

    mutex.lock();

    if (outFile->IsOpened())
    {
        *outFile << text << END_LINE;
    }

#ifdef DEBUG

    ConsoleLog::Write(text);

#endif

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
    
    if (GetStdHandle(STD_OUTPUT_HANDLE) == nullptr)
    {
        /*
        *  ����� � ������� �� ���������� ���������� ������ ������� ����, ����� ������������� ����� Lucida Console
        */

        win::SetConsoleCP(1251);
        
        if (!SetConsoleOutputCP(1251))
        {
            DISPLAY_LAST_ERROR();
        }

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
    if (!FreeConsole())
    {
        DISPLAY_LAST_ERROR();
    }
#endif
}


void ConsoleLog::Write(pchar message)
{
#ifdef WIN32

    if (handle)
    {
        if(!WriteConsoleA(handle, (void *)message, (DWORD)std::strlen(message), NULL, NULL))
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

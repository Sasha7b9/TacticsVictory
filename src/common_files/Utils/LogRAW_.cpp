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


void LogRAW::Create(pchar nameLog, bool /*new_console*/)
{
    outFile = new FS::File();

    ConsoleLog::Create();

    outFile->Create((std::string("log") + FS::delimiter + nameLog).c_str());
}

void LogRAW::Destroy()
{
    ConsoleLog::Destroy();

    delete outFile;
}


void LogRAW::CommonWriteF(pchar file, int line, std::vector<char> &v, pchar symbols)
{
    file = ExtractName(file, numSymbolsForMarker - SU::Length(STR_ERROR) - 1);

    snprintf(const_cast<char *const>(v.data()), 1024, "%s:%d ", file, line);

    while (SU::Length(v.data()) < numSymbolsForMarker - SU::Length(STR_ERROR) - 1)
    {
        strcat(v.data(), " ");
    }

    std::strcat(v.data(), symbols);
    std::strcat(v.data(), " | ");

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
    file = ExtractName(file, numSymbolsForMarker);

    std::vector<char> v(1024);

    snprintf(const_cast<char *const>(v.data()), 1024, "%s:%d ", file, line);

    while (SU::Length(v.data()) < numSymbolsForMarker)
    {
        std::strcat(v.data(), " ");
    }

    snprintf((char *const)v.data() + std::strlen(v.data()), 1024, "| %s %s", symbols, text);

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

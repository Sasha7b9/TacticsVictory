#include "stdafx.h"
#include <mutex>


#ifdef WIN32
#pragma warning(push)
#pragma warning(disable: 4996)  // warning C4996: 'strcat': This function or variable may be unsafe. Consider using strcat_s instead.
#endif


static const int numSymbolsForMarker = 40;          // Количество сиволов под позицию ошибки

static pchar strERROR = "*ERROR*";
static pchar strWARNING = "*WARNING*";

static FS::File *outFile;

#ifdef WIN32
HANDLE ConsoleLog::handle = nullptr;
#endif


static pchar ExtractName(pchar fullName, int max)
{
    pchar pointer = fullName + SU::Length(fullName) - 1; //-V104 //-V2563

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

    return pointer + (length < max ? 2 : 6); //-V2563
}


void Log::Create(pchar nameLog)
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

void Log::Destroy()
{
    ConsoleLog::Destroy();

    delete outFile;
}


void Log::Error(pchar file, int line, pchar format, ...)
{
    file = ExtractName(file, numSymbolsForMarker - SU::Length(strERROR) - 1); //-V2513 //-V202

    std::va_list args;
    va_start(args, format);

    std::vector<char> v(1024);

    snprintf(const_cast<char *const>(v.data()), 1024, "%s:%d ", file, line);

    while (SU::Length(v.data())  < numSymbolsForMarker - SU::Length(strERROR) - 1) //-V806 //-V814 PVS выдаёт ложные предупреждения //-V2513
    {
        strcat(v.data(), " "); //-V2513
    }

    std::strcat(v.data(), strERROR); //-V2513
    std::strcat(v.data(), " | "); //-V2513

    std::vsnprintf(v.data() + SU::Length(v.data()), v.size(), format, args); //-V806 Ложное предупреждение PVS //-V2513 //-V2563 //-V104

    va_end(args);

    if (outFile->IsOpened())
    {
        *outFile << v.data() << "\n";
    }

#ifdef DEBUG

    ConsoleLog::Write(v.data());

#endif
}


void Log::Warning(pchar file, int line, pchar format, ...)
{
    file = ExtractName(file, numSymbolsForMarker - SU::Length(strWARNING) - 1); //-V2513 //-V202

    std::va_list args;
    va_start(args, format);

    std::vector<char> v(1024);

    snprintf(const_cast<char *const>(v.data()), 1024, "%s:%d ", file, line);

    while (SU::Length(v.data()) < numSymbolsForMarker - SU::Length(strWARNING) - 1) //-V806 //-V814 PVS выдаёт ложное предупреждение //-V2513
    {
        std::strcat(v.data(), " "); //-V2513
    }

    std::strcat(v.data(), strWARNING); //-V2513
    std::strcat(v.data(), " | "); //-V2513

    std::vsnprintf(v.data() + SU::Length(v.data()), v.size(), format, args); //-V806 PVS выдаёт ложное предупреждение //-V2513 //-V2563 //-V104

    va_end(args);

    if (outFile->IsOpened())
    {
        *outFile << v.data() << "\n";
    }

#ifdef DEBUG

    ConsoleLog::Write(v.data());

#endif 
}


void Log::Write(pchar file, int line, pchar format, ...)
{
    static std::mutex mutex;

    mutex.lock();

    file = ExtractName(file, numSymbolsForMarker);

    std::va_list args;
    va_start(args, format);

    std::vector<char> v(1024);

    snprintf(const_cast<char *const>(v.data()), 1024, "%s:%d ", file, line);

    while (SU::Length(v.data()) < numSymbolsForMarker) //-V806 //-V814 PVS выдаёт ложное предупреждение //-V2513
    {
        std::strcat(v.data(), " "); //-V2513
    }

    std::strcat(v.data(), "| "); //-V2513

    std::vsnprintf(v.data() + SU::Length(v.data()) , v.size(), format, args); //-V806 PVS выдаёт ложное предупреждение //-V2513 //-V2563 //-V104

    va_end(args);

    if (outFile->IsOpened())
    {
        *outFile << v.data() << "\n";
    }

#ifdef DEBUG

    ConsoleLog::Write(v.data());

#endif

    mutex.unlock();
}


Log::~Log()
{
    LOG_WRITE("Close application");
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
        *  Чтобы в консоли не выводились кракозяблы вместо русских букв, нужно устанавливать шрифт Lucida Console
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
        if(!WriteConsoleA(handle, (void *)message, (DWORD)std::strlen(message), NULL, NULL)) //-V202
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

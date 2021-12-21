// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


#ifdef LOG_WRITE
#undef LOG_WRITE
#endif

#define FUNC_ENTER()           LOG_WRITE("%s enter", __FUNCTION__);
#define FUNC_LEAVE()           LOG_WRITE("%s leave", __FUNCTION__);

#define LOG_WRITE(...)         Log::Write(__VA_ARGS__);
#define LOG_WRITE_TRACE(...)   Log::WriteTrace(__FILE__, __LINE__, __VA_ARGS__);

#define LOG_WARNING(...)       Log::Warning(__VA_ARGS__);
#define LOG_WARNING_TRACE(...) Log::WarningTrace(__FILE__, __LINE__, __VA_ARGS__);


#define LOG_ERROR(...)         Log::Error(__VA_ARGS__);
#define LOG_ERROR_TRACE(...)   Log::ErrorTrace(__FILE__, __LINE__, __VA_ARGS__);


namespace Pi
{
    namespace FlagLog
    {
        typedef uint B;

        const B Raw     = 1 << 0;       // Запись обычных сообщений будет производиться в лог
        const B Warning = 1 << 1;       // Запись предупреждающих сообщений будет произвоиться в лог
        const B Error   = 1 << 2;       // Запись сообщений оо ошибках будет производиться в лог
        const B All     = Raw | Warning | Error;
    }


    namespace DirectionLog
    {
        typedef uint B;

        const B EngineReport  = 1 << 0;     // Направлять сообщения в консоль движка
        const B SystemConsole = 1 << 1;     // Направлять сообщения в системную консоль
        const B File          = 1 << 2;     // Направлять сообщения в файл
        const B All           = EngineReport | SystemConsole | File;
    }


    class Log
    {
    public:

        static void Construct(FlagLog::B flags = FlagLog::All, DirectionLog::B direction = DirectionLog::All);

        static void Destruct();

        static void Write(pchar format, ...);

        static void WriteTrace(pchar name_file, int num_line, pchar format, ...);

        static void Warning(pchar format, ...);

        static void WarningTrace(pchar name_file, int num_line, pchar format, ...);

        static void Error(pchar format, ...);

        static void ErrorTrace(pchar name_file, int num_line, pchar format, ...);

    private:

        static void WriteMessage(pchar message);

        static FlagLog::B flags;

        static DirectionLog::B direction;

        static File *file;

#ifdef WIN32

        static HANDLE handleConsole;

#endif
    };
}
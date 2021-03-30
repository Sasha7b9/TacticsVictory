#pragma once


#define LOG_WRITE(...) Log::Write(__FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) Log::Error(__FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARNING(...) Log::Warning(__FILE__, __LINE__, __VA_ARGS__);


class Log
{
public:

    static void Create(pchar nameLog);

    static void Destroy();

    //+V576,class:Log,function:Error,format_arg:3,ellipsis_arg:4
    static void Error(pchar file, int line, pchar format, ...);

    //+V576,class:Log,function:Write,format_arg:3,ellipsis_arg:4
    static void Write(pchar file, int line, pchar format, ...);

    //+V576,class:Log,function:Warning,format_arg:3,ellipsis_arg:4
    static void Warning(pchar file, int line, pchar format, ...);

private:
    virtual ~Log();
};


struct ConsoleLog
{
    static void Create();
    
    static void Write(pchar message);

    static void Destroy();

#ifdef WIN32
    static HANDLE handle;
#endif
};
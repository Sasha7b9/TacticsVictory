#pragma once


// Информационные сообщения.
#define LOGWRITE(...)    LogRAW::WriteF(__FILE__, __LINE__, __VA_ARGS__)
#define LOGWRITEF(...)   LogRAW::WriteF(__FILE__, __LINE__, __VA_ARGS__)

// Некритичные ошибки
#define LOGWARNING(...)  LogRAW::Warning(__FILE__, __LINE__, __VA_ARGS__);
#define LOGWARNINGF(...) LogRAW::Warning(__FILE__, __LINE__, __VA_ARGS__);

// Критичные ошибки.
#define LOGERROR(...)    LogRAW::Error(__FILE__, __LINE__, __VA_ARGS__)
#define LOGERRORF(...)   LogRAW::Error(__FILE__, __LINE__, __VA_ARGS__)


class LogRAW
{
public:

    static void Create(pchar nameLog);

    static void Destroy();

    //+V576,class:Log,function:Error,format_arg:3,ellipsis_arg:4
    static void Error(pchar file, int line, pchar format, ...);

    //+V576,class:Log,function:Write,format_arg:3,ellipsis_arg:4
    static void WriteF(pchar file, int line, pchar format, ...);
    static void Write(pchar file, int line, pchar text);
    static void Write(pchar text);

    //+V576,class:Log,function:Warning,format_arg:3,ellipsis_arg:4
    static void Warning(pchar file, int line, pchar format, ...);

private:
    virtual ~LogRAW();
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
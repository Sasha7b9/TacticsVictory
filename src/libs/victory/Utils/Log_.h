#pragma once


// Информационные сообщения.
#define LOGWRITE(x)      LogRAW::Write(__FILE__, __LINE__, x)
#define LOGWRITEF(...)   LogRAW::WriteF(__FILE__, __LINE__, __VA_ARGS__)

// Некритичные ошибки
#define LOGWARNING(x)    LogRAW::Warning(__FILE__, __LINE__, x);
#define LOGWARNINGF(...) LogRAW::WarningF(__FILE__, __LINE__, __VA_ARGS__);

// Критичные ошибки.
#define LOGERROR(x)      LogRAW::Error(__FILE__, __LINE__, x)
#define LOGERRORF(...)   LogRAW::ErrorF(__FILE__, __LINE__, __VA_ARGS__)

#define LOG_FUNC_ENTER() LogRAW::WriteF(__FILE__, __LINE__, ">>>>>>>>> %s", __FUNCTION__)


class LogRAW
{
public:

    // Если create_console == true, то нужно создавать новую консоль
    static void Create(pchar nameLog, bool create_console);

    static void Destroy();

    //+V576,class:Log,function:Write,format_arg:3,ellipsis_arg:4
    static void WriteF(pchar file, int line, pchar format, ...);
    static void Write(pchar file, int line, pchar text);
    static void Write(pchar text);

    //+V576,class:Log,function:Warning,format_arg:3,ellipsis_arg:4
    static void WarningF(pchar file, int line, pchar format, ...);
    static void Warning(pchar file, int line, pchar text);

    //+V576,class:Log,function:Error,format_arg:3,ellipsis_arg:4
    static void ErrorF(pchar file, int line, pchar format, ...);
    static void Error(pchar file, int line, pchar text);

private:
    virtual ~LogRAW();

    static void CommonWrite(pchar file, int line, pchar text, pchar symbols);
    static void CommonWriteF(pchar file, int line, std::vector<char> &v, pchar symbols);
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

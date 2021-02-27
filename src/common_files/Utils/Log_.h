// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class LogT : public Log
{
    URHO3D_OBJECT(LogT, Log);

public:
    LogT(Context *context = TheContext);
    virtual void Write(int level, const String &message, pchar file, pchar func, int numLine);
    void EnableExtendedInfo();
    void DisableExtendedInfo();

protected:
    static bool enabledExtendedInfo;
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


#define LOGINFO(message)        TheLog->Write(LOG_INFO, message, __FILE__, __FUNCTION__, __LINE__)
#define LOGINFOF(format, ...)   TheLog->Write(LOG_INFO, ToString(format, ##__VA_ARGS__), __FILE__, __FUNCTION__, __LINE__)
#define LOGERROR(message)       TheLog->Write(LOG_ERROR, message, __FILE__, __FUNCTION__, __LINE__)
#define LOGERRORF(format, ...)  TheLog->Write(LOG_ERROR, ToString(format, ##__VA_ARGS__), __FILE__, __FUNCTION__, __LINE__)

// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


extern Context *TheContext;


class TLog : public Log
{
    URHO3D_OBJECT(TLog, Log);

public:
    TLog(Context *context = TheContext);
    static void Write(int level, const String &message, char *file, char *func, int numLine);
    static void EnableExtendedInfo();
    static void DisableExtendedInfo();

private:
    static bool enabledExtendedInfo;
};


#define LOGINFO(message)        TLog::Write(LOG_INFO, message, __FILE__, __FUNCTION__, __LINE__)
#define LOGINFOF(format, ...)   TLog::Write(LOG_INFO, ToString(format, ##__VA_ARGS__), __FILE__, __FUNCTION__, __LINE__)
#define LOGERROR(message)       TLog::Write(LOG_ERROR, message, __FILE__, __FUNCTION__, __LINE__)
#define LOGERRORF(format, ...)  TLog::Write(LOG_ERROR, ToString(format, ##__VA_ARGS__), __FILE__, __FUNCTION__, __LINE__)

// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class LogRTS : public Log
{
    URHO3D_OBJECT(LogRTS, Log);

public:
    LogRTS(Context *context = TheContext);
    static void Write(int level, const String &message, char *file, char *func, int numLine);
    static void EnableExtendedInfo();
    static void DisableExtendedInfo();

private:
    static bool enabledExtendedInfo;

    DEFAULT_MEMBERS(LogRTS);
};


#define LOGINFO(message)        LogRTS::Write(LOG_INFO, message, __FILE__, __FUNCTION__, __LINE__)
#define LOGINFOF(format, ...)   LogRTS::Write(LOG_INFO, ToString(format, ##__VA_ARGS__), __FILE__, __FUNCTION__, __LINE__)
#define LOGERROR(message)       LogRTS::Write(LOG_ERROR, message, __FILE__, __FUNCTION__, __LINE__)
#define LOGERRORF(format, ...)  LogRTS::Write(LOG_ERROR, ToString(format, ##__VA_ARGS__), __FILE__, __FUNCTION__, __LINE__)

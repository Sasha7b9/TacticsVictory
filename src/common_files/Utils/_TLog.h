// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


extern Context *TheContext;


class LogTV : public Log
{
    URHO3D_OBJECT(LogTV, Log);

public:
    LogTV(Context *context = TheContext);
    static void Write(int level, const String &message, char *file, char *func, int numLine);
    static void EnableExtendedInfo();
    static void DisableExtendedInfo();

private:
    static bool enabledExtendedInfo;
};


#define LOGINFO(message)        LogTV::Write(LOG_INFO, message, __FILE__, __FUNCTION__, __LINE__)
#define LOGINFOF(format, ...)   LogTV::Write(LOG_INFO, ToString(format, ##__VA_ARGS__), __FILE__, __FUNCTION__, __LINE__)
#define LOGERROR(message)       LogTV::Write(LOG_ERROR, message, __FILE__, __FUNCTION__, __LINE__)
#define LOGERRORF(format, ...)  LogTV::Write(LOG_ERROR, ToString(format, ##__VA_ARGS__), __FILE__, __FUNCTION__, __LINE__)

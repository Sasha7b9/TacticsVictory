// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class LogU3D : public Log
{
    URHO3D_OBJECT(LogU3D, Log);

public:
    LogU3D(LogU3D **self);
    virtual ~LogU3D();
    virtual void Write(int level, const String &message, pchar file, pchar func, int numLine);
    void EnableExtendedInfo();
    void DisableExtendedInfo();

protected:
    static bool enabledExtendedInfo;
};


#define LOGINFO(message)         TheLog->Write(LOG_INFO, message, __FILE__, __FUNCTION__, __LINE__)
#define LOGINFOF(format, ...)    TheLog->Write(LOG_INFO, ToString(format, ##__VA_ARGS__), __FILE__, __FUNCTION__, __LINE__)
#define LOGWRITE(message)        TheLog->Write(LOG_INFO, message, __FILE__, __FUNCTION__, __LINE__)
#define LOGWRITEF(format, ...)   TheLog->Write(LOG_INFO, ToString(format, ##__VA_ARGS__), __FILE__, __FUNCTION__, __LINE__)
#define LOGERROR(message)        TheLog->Write(LOG_ERROR, message, __FILE__, __FUNCTION__, __LINE__)
#define LOGERRORF(format, ...)   TheLog->Write(LOG_ERROR, ToString(format, ##__VA_ARGS__), __FILE__, __FUNCTION__, __LINE__)
#define LOGWARNING(message)      TheLog->Write(LOG_WARNING, message, __FILE__, __FUNCTION__, __LINE__)
#define LOGWARNINGF(format, ...) TheLog->Write(LOG_WARNING, ToString(format, ##__VA_ARGS__), __FILE__, __FUNCTION__, __LINE__)

//#define LOG_FUNC_ENTER()  URHO3D_LOGINFOF(">>>>>>>>>>>>>>>            %s", __FUNCTION__);
#define LOG_FUNC_ENTER() LOGINFOF(">>>>>>>>>>>>>>>            %s", __FUNCTION__)

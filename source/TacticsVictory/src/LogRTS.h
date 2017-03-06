#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LogRTS : public Log
{
    URHO3D_OBJECT(LogRTS, Log);

public:
    LogRTS(Context *context = gContext);
    static void Write(int level, const String &message, char *file, char *func, int numLine);
    static void EnableExtendedInfo();
    static void DisableExtendedInfo();

private:
    static bool enabledExtendedInfo;

    DEFAULT_MEMBERS(LogRTS);
};


#define LOG_INFOF(format, ...) LogRTS::Write(LOG_INFO, ToString(format, ##__VA_ARGS__), __FILE__, __FUNCTION__, __LINE__)

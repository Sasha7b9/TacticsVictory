// 2021/02/17 13:43:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Utils/Log_.h"


class CLog : public TLog
{
    URHO3D_OBJECT(CLog, TLog);

public:
    CLog(Context *context = TheContext) : TLog(context) {}
    virtual ~CLog();

    virtual void Write(int level, const String &message, char *file, char *func, int numLine) override;
};

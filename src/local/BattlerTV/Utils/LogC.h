// 2021/02/17 13:43:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Utils/Log_.h"


class LogC : public LogT
{
    URHO3D_OBJECT(LogC, LogT);

public:
    LogC(Context *context = TheContext) : LogT(context) {}
    virtual ~LogC();

    virtual void Write(int level, const String &message, pchar file, pchar func, int numLine) override;
};

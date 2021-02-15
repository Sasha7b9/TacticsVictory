// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "WindowRTS.h"



class Tab : public WindowRTS
{
    URHO3D_OBJECT(Tab, WindowRTS);

public:
    Tab(Context *context = TheContext);
    static void RegisterObject(Context *context = TheContext);
    static SharedPtr<Tab> Create(char *title);

    SharedPtr<ButtonToggled> buttonTitle;

    DEFAULT_MEMBERS(Tab);
};

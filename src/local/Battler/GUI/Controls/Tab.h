#pragma once
#include "WindowRTS.h"



class Tab : public WindowRTS
{
    URHO3D_OBJECT(Tab, WindowRTS);

public:
    Tab(Context *context = gContext);
    static void RegisterObject(Context *context = gContext);
    static SharedPtr<Tab> Create(char *title);

    SharedPtr<ButtonToggled> buttonTitle;

    DEFAULT_MEMBERS(Tab);
};

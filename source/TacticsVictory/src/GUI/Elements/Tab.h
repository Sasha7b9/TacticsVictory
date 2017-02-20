#pragma once


#include "GUI/Elements/Window.h"


class Tab : public lWindow
{
    URHO3D_OBJECT(Tab, lWindow);

public:
    Tab(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

    static SharedPtr<Tab> Create(char *title);

    SharedPtr<ButtonToggled> buttonTitle;
};
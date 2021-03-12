// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Window_.h"


class Tab : public WindowT
{
    URHO3D_OBJECT(Tab, WindowT);

public:
    Tab(Context *context);
    static void RegisterObject();

    static SharedPtr<Tab> Create(char *title);

    SharedPtr<ButtonToggled> buttonTitle;
};

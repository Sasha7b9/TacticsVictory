// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/_TWindow.h"


class Tab : public WindowTV
{
    URHO3D_OBJECT(Tab, WindowTV);

public:
    Tab(Context *context = TheContext);
    static void RegisterObject(Context *context = TheContext);
    static SharedPtr<Tab> Create(char *title);

    SharedPtr<ButtonToggled> buttonTitle;
};

// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/TWindow_.h"


class Tab : public TWindow
{
    URHO3D_OBJECT(Tab, TWindow);

public:
    Tab(Context *context = TheContext);
    static void RegisterObject(Context *context = TheContext);
    static SharedPtr<Tab> Create(char *title);

    SharedPtr<ButtonToggled> buttonTitle;
};

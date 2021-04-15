// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Window_.h"


class Tab : public Control
{
    URHO3D_OBJECT(Tab, Control);

public:
    Tab(Context *);
    static void RegisterObject();

    static SharedPtr<Tab> Create(char *title);

    SharedPtr<ButtonToggled> buttonTitle;
};

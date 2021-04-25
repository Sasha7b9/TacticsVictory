// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Control_.h"


class Tab : public Control
{
    URHO3D_OBJECT(Tab, Control);

public:
    Tab(Context *);
    static void RegisterObject();

    static SharedPtr<Tab> Create(pchar title);

    SharedPtr<ButtonToggled> buttonTitle;
};

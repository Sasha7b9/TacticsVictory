// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUi/Controls/Buttons/ButtonSwitch_.h"
#include "GUI/Menu/MenuPage_.h"


class MenuStart : public MenuPage
{
    URHO3D_OBJECT(MenuStart, MenuPage);

public:
    MenuStart();
    ~MenuStart();

private:
    void HandleButtonRelease(StringHash, VariantMap&);

    SharedPtr<ButtonT>      buttonPlay;
    SharedPtr<ButtonT>      buttonOptions;
    SharedPtr<ButtonT>      buttonExit;
};

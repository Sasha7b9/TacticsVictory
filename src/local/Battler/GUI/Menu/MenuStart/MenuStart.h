// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUi/Controls/Buttons/ButtonSwitch_.h"
#include "GUI/Menu/WindowMenu_.h"


class MenuStart : public WindowMenu
{
    URHO3D_OBJECT(MenuStart, WindowMenu);

public:
    MenuStart();
    ~MenuStart();

private:
    void HandleButtonRelease(StringHash, VariantMap&);

    SharedPtr<ButtonT>      buttonPlay;
    SharedPtr<ButtonT>      buttonOptions;
    SharedPtr<ButtonT>      buttonAboutGame;
    SharedPtr<ButtonT>      buttonAboutMe;
    SharedPtr<ButtonT>      buttonExit;
};

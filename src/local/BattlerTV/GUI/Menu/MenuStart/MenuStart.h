// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUi/Controls/ButtonSwitch_.h"
#include "GUI/Menu/WindowMenu.h"


class MenuStart : public WindowMenu
{
    URHO3D_OBJECT(MenuStart, WindowMenu);

public:
    MenuStart();
    ~MenuStart();

private:
    void HandleButtonRelease(StringHash, VariantMap&);

    SharedPtr<ButtonSwitch> buttonLanguage;
    SharedPtr<ButtonT>      buttonPlay;
    SharedPtr<ButtonT>      buttonEditor;
    SharedPtr<ButtonT>      buttonOptions;
    SharedPtr<ButtonT>      buttonAboutGame;
    SharedPtr<ButtonT>      buttonAboutMe;
    SharedPtr<ButtonT>      buttonExit;
};

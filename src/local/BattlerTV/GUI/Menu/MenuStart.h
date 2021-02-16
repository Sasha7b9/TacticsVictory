// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/WindowMenu.h"


class MenuStart : public WindowMenu
{
    URHO3D_OBJECT(MenuStart, WindowMenu);

public:
    MenuStart(Context *context = TheContext);
    ~MenuStart();

private:
    void HandleButtonRelease(StringHash, VariantMap&);

    SharedPtr<ButtonTV> buttonServer;
    SharedPtr<ButtonTV> buttonClient;
    SharedPtr<ButtonTV> buttonEditor;
    SharedPtr<ButtonTV> buttonExit;
    SharedPtr<ButtonTV> buttonOptions;
    SharedPtr<ButtonTV> buttonHelp;
    SharedPtr<ButtonTV> buttonAboutGame;
    SharedPtr<ButtonTV> buttonAboutMe;
    SharedPtr<ButtonSwitch> buttonLanguage;
};

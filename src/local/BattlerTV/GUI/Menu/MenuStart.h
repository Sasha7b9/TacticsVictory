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

    SharedPtr<ButtonRTS> buttonServer;
    SharedPtr<ButtonRTS> buttonClient;
    SharedPtr<ButtonRTS> buttonEditor;
    SharedPtr<ButtonRTS> buttonExit;
    SharedPtr<ButtonRTS> buttonOptions;
    SharedPtr<ButtonRTS> buttonHelp;
    SharedPtr<ButtonRTS> buttonAboutGame;
    SharedPtr<ButtonRTS> buttonAboutMe;
    SharedPtr<ButtonSwitch> buttonLanguage;
};

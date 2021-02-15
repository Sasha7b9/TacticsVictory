// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/WindowMenu.h"
#include "GUI/Controls/_Button.h"
#include "GUI/Controls/_ButtonSwitch.h"



class MenuAboutMe;



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

    DEFAULT_MEMBERS(MenuStart);
};

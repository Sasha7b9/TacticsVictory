#pragma once
#include "GUI/Menu/WindowMenu.h"
#include "GUI/Controls/Button.h"
#include "GUI/Controls/ButtonSwitch.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MenuAboutMe;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MenuStart : public WindowMenu
{
    URHO3D_OBJECT(MenuStart, WindowMenu);

public:
    MenuStart(Context *context = gContext);
    ~MenuStart();
    bool Enabled();

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

    MenuAboutMe *windowAboutMe = nullptr;
};

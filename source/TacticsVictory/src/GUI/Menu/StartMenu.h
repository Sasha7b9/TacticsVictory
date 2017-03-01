#pragma once
#include "GUI/Elements/Window.h"
#include "GUI/Elements/Button.h"
#include "GUI/Elements/ButtonSwitch.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StartMenu : public WindowRTS
{
    URHO3D_OBJECT(StartMenu, WindowRTS);

public:
    StartMenu(Context *context = gContext);

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

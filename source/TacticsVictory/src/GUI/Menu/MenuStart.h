#pragma once
#include "GUI/Controls/Window.h"
#include "GUI/Controls/Button.h"
#include "GUI/Controls/ButtonSwitch.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MenuAboutMe;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MenuStart : public WindowRTS
{
    URHO3D_OBJECT(MenuStart, WindowRTS);

public:
    MenuStart(Context *context = gContext);

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

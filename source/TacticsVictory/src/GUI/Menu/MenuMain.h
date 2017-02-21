#pragma once


#include "GUI/Elements/Window.h"


class ButtonSwitch;


class MenuMain : public WindowRTS
{
    URHO3D_OBJECT(MenuMain, WindowRTS);

public:
    MenuMain(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

private:
    MenuMain& operator=(const MenuMain&)
    {};

    void HandleButtonRelease(StringHash eventType, VariantMap& eventData);

    SharedPtr<ButtonMain> buttonNewGame;
    SharedPtr<ButtonMain> buttonEditor;
    SharedPtr<ButtonMain> buttonExit;
    SharedPtr<ButtonMain> buttonOptions;
    SharedPtr<ButtonSwitch> buttonLanguage;
};
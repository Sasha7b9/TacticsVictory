#pragma once
#include "GUI/Elements/Window.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ButtonSwitch;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MenuMain : public WindowRTS
{
    URHO3D_OBJECT(MenuMain, WindowRTS);

public:
    MenuMain(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);
    void Open();
    void Close();

private:
    void HandleButtonRelease(StringHash, VariantMap&);  

    SharedPtr<ButtonRTS> buttonNewGame;
    SharedPtr<ButtonRTS> buttonEditor;
    SharedPtr<ButtonRTS> buttonExit;
    SharedPtr<ButtonRTS> buttonOptions;
    SharedPtr<ButtonSwitch> buttonLanguage;
    SharedPtr<ButtonRTS> buttonCancel;
};

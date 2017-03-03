#pragma once
#include "GUI/Menu/WindowMenu.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MenuConfirmExit : public WindowMenu
{
    URHO3D_OBJECT(MenuConfirmExit, WindowMenu);

public:
    MenuConfirmExit(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

private:
    SharedPtr<ButtonRTS> buttonOk;
    SharedPtr<ButtonRTS> buttonCancel;

    void HandleButtonRelease(StringHash eventType, VariantMap& eventData);
    void OnPressButtonOk();
    void OnPressButtonCancel();
};

#pragma once
#include "GUI/Controls/Window.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MenuConfirmExit : public WindowRTS
{
    URHO3D_OBJECT(MenuConfirmExit, WindowRTS);

public:
    MenuConfirmExit(Context *context);

    static void RegisterObject(Context *context = gContext);

private:
    SharedPtr<ButtonRTS> buttonOk;
    SharedPtr<ButtonRTS> buttonCancel;

    void HandleButtonRelease(StringHash eventType, VariantMap& eventData);
    void OnPressButtonOk();
    void OnPressButtonCancel();
};

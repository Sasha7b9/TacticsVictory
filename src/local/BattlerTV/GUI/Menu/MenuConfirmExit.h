// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/WindowMenu.h"



class MenuConfirmExit : public WindowMenu
{
    URHO3D_OBJECT(MenuConfirmExit, WindowMenu);

public:
    MenuConfirmExit(Context *context = TheContext);

    static void RegisterObject(Context *context = TheContext);

private:
    SharedPtr<ButtonRTS> buttonOk;
    SharedPtr<ButtonRTS> buttonCancel;

    void HandleButtonRelease(StringHash eventType, VariantMap& eventData);
    void OnPressButtonOk();
    void OnPressButtonCancel();

    DEFAULT_MEMBERS(MenuConfirmExit);
};

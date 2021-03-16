// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/WindowMenu.h"


class MenuConfirmExit : public WindowMenu
{
    URHO3D_OBJECT(MenuConfirmExit, WindowMenu);

public:
    MenuConfirmExit(Context *);
    static void RegisterObject();

private:
    SharedPtr<ButtonT> buttonOk;
    SharedPtr<ButtonT> buttonCancel;

    void HandleButtonRelease(StringHash eventType, VariantMap& eventData);
    void OnPressButtonOk();
    void OnPressButtonCancel();
};

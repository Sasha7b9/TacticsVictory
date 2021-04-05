// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/MenuPage_.h"


class MenuConfirmExit : public MenuPage
{
    URHO3D_OBJECT(MenuConfirmExit, MenuPage);

public:
    MenuConfirmExit();

private:
    SharedPtr<ButtonT> buttonOk;
    SharedPtr<ButtonT> buttonCancel;

    void HandleButtonRelease(StringHash eventType, VariantMap& eventData);
    void OnPressButtonOk();
    void OnPressButtonCancel();
};

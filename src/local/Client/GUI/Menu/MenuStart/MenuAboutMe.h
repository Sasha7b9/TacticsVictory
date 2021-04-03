// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/WindowMenu_.h"


class MenuAboutMe : public WindowMenu
{
    URHO3D_OBJECT(MenuAboutMe, WindowMenu);

public:
    MenuAboutMe();

private:
    SharedPtr<ButtonT> buttonOk;

    void HandleButtonRelease(StringHash, VariantMap&);
};

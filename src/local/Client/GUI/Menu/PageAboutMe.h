// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/MenuPage_.h"


class MenuAboutMe : public MenuPage
{
    URHO3D_OBJECT(MenuAboutMe, MenuPage);

public:
    MenuAboutMe();

private:
    SharedPtr<ButtonT> buttonOk;

    void HandleButtonRelease(StringHash, VariantMap&);
};

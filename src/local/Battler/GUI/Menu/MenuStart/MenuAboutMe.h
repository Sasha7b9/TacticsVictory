// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/MenuPage_.h"


class PageAboutMe : public MenuPage
{
    URHO3D_OBJECT(PageAboutMe, MenuPage);

public:
    PageAboutMe();

private:
    SharedPtr<ButtonT> buttonOk;

    void HandleButtonRelease(StringHash, VariantMap&);
};

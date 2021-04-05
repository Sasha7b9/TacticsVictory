// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUi/Controls/Buttons/ButtonSwitch_.h"
#include "GUI/Menu/MenuPage_.h"


class PageMain : public MenuPage
{
    URHO3D_OBJECT(PageMain, MenuPage);

public:
    PageMain();
    ~PageMain();

private:
    void HandleButtonRelease(StringHash, VariantMap&);

    SharedPtr<ButtonT>      buttonPlay;
    SharedPtr<ButtonT>      buttonExit;
};

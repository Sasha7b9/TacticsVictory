// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUi/Controls/Buttons/ButtonSwitch_.h"
#include "GUI/Menu/MenuPage_.h"


class PageStart : public MenuPage
{
    URHO3D_OBJECT(PageStart, MenuPage);

public:
    PageStart();
    ~PageStart();

private:
    void HandleButtonRelease(StringHash, VariantMap&);

    SharedPtr<ButtonSwitch> buttonLanguage;
    SharedPtr<ButtonT>      buttonPlay;
    SharedPtr<ButtonT>      buttonEditor;
    SharedPtr<ButtonT>      buttonOptions;
    SharedPtr<ButtonT>      buttonAboutGame;
    SharedPtr<ButtonT>      buttonAboutMe;
    SharedPtr<ButtonT>      buttonExit;
};

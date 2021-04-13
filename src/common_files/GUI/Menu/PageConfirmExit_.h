// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/MenuPage_.h"


class PageConfirmExit : public MenuPage
{
    URHO3D_OBJECT(PageConfirmExit, MenuPage);

public:
    PageConfirmExit();

private:
    SharedPtr<ButtonT> buttonOk;
    SharedPtr<ButtonT> buttonCancel;

    void HandlerButtonRelease(StringHash eventType, VariantMap& eventData);
    void OnPressButtonOk();
    void OnPressButtonCancel();
};

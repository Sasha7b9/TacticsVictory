// 2021/04/13 11:26:09 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Cursor_.h"
#include "GUI/GUI_.h"
#include "GUI/Controls/GovernorFloat_.h"
#include "GUI/Controls/Buttons/Button_.h"
#include "GUI/Controls/Buttons/ButtonSwitch_.h"
#include "GUI/Controls/Sliders/Slider_.h"
#include "GUI/Controls/Sliders/SliderInt_.h"
#include "GUI/Menu/PageConfirmExit_.h"


GUIT::GUIT(GUIT **self) : Object(TheContext)
{
    RegistrationObjects();

    *self = this;
}


void GUIT::RegistrationObjects()
{
    ButtonT::RegisterObject();
    ButtonSwitch::RegisterObject();
    ButtonToggled::RegisterObject();
    CursorT::RegisterObject();
    WindowT::RegisterObject();
    PageConfirmExit::RegisterObject();
    Label::RegisterObject();
    SliderT::RegisterObject();
    SliderInt::RegisterObject();
    GovernorCell::RegisterObject();
    GovernorFloat::RegisterObject();
    SliderWithTextAndButtons::RegisterObject();
    DropDownListWithTextAndButton::RegisterObject();
}


bool GUIT::UnderCursor()
{
    PODVector<UIElement *> elements;
    TheUIRoot->GetChildren(elements);

    for (UIElement *elem : elements)
    {
        if (elem->GetName() != "Cursor" && elem->IsVisible() && elem->IsInside(TheCursor->GetCursor()->GetPosition(), true))
        {
            return true;
        }
    }

    return false;
}

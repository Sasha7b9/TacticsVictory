// 2021/02/24 15:45:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Cursor_.h"
#include "Input/Mouse_.h"
#include "Scene/Objects/Units/UnitsEvents_.h"


Mouse::Mouse(Mouse **self) : Object(TheContext)
{
    SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(Mouse, HandleMouseDown));

    *self = this;
}


void Mouse::HandleMouseDown(StringHash, VariantMap &eventData)
{
    int buttons = static_cast<int>(eventData[MouseButtonDown::P_BUTTONS].GetInt());

    if (buttons == MOUSEB_LEFT)
    {
        ProcessMouseLeft();
    }
    else if (buttons == MOUSEB_RIGHT)
    {
        ProcessMouseRight();
    }
}

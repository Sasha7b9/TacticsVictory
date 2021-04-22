// 2021/02/24 15:45:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Cursor_.h"
#include "Input/Mouse_v.h"
#include "Scene/Objects/Units/UnitsEvents_.h"


Mouse::Mouse(Mouse **self, Context *context) : Object(context)
{
    SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(Mouse, HandlerMouseDown));

    *self = this;
}


void Mouse::HandlerMouseDown(StringHash, VariantMap &eventData)
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

#ifndef USE_MOUSE

void Mouse::ProcessMouseLeft()
{

}


void Mouse::ProcessMouseRight()
{

}


#endif

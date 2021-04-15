// 2021/04/15 15:05:24 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Windows/Window_.h"


WindowT::WindowT(pchar _title) : Control(TheContext)
{
    title = Label::Create(_title, 20, 120, -1);
    title->SetAlignment(HA_LEFT, VA_TOP);
    title->SetTemporary(HA_LEFT);
    AddChild(title);

    SubscribeToEvent(this, E_RESIZED, URHO3D_HANDLER(WindowT, HandlerResize));
}


void WindowT::HandlerResize(StringHash, VariantMap &)
{
    CallbackOnResize();
}

// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/GuiGame/WindowTarget.h"


WindowTarget::WindowTarget(Context *context) :
    WindowT(context)
{
    SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("WindowNoBorder");

    SetFixedSize(WIDTH, HEIGHT);
}

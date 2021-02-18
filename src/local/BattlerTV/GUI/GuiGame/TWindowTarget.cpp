// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/GuiGame/TWindowTarget.h"


WindowTarget::WindowTarget(Context *context) :
    TWindow(context)
{
    SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("WindowNoBorder");

    SetFixedSize(WIDTH_WINDOW_TARGET, HEIGHT_WINDOW_TARGET);
}

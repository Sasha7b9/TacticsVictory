#include <stdafx.h>


#include "ContextMenuUnit.h"


ContextMenuUnit::ContextMenuUnit(Context *context) :
    lWindow(context)
{
    SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("WindowBorder");

    SetFixedSize(150, 150);
}
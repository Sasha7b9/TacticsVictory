// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/Label_.h"
#include "GUI/Controls/Buttons/ButtonToggled_.h"
#include "GUI/GuiGame/ContextMenuUnit.h"
#include "GUI/GuiGame/WindowTarget.h"


ContextMenuUnit::ContextMenuUnit() :
    Control(TheContext)
{
    SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("WindowBorder");

    SetLayout(LM_VERTICAL, 3, IntRect(3, 3, 3, 3));
    title = Label::Create("", true, 8);
    title->SetAlignment(HA_CENTER, VA_TOP);
    AddChild(title);
}


void ContextMenuUnit::Create(ObjectT *object_)
{
    object = object_;
}


void ContextMenuUnit::CreateForUnit()
{
    SharedPtr<ButtonToggled> button(new ButtonToggled(nullptr, "Field View", 100));
    SubscribeToEvent(button, E_TOGGLED, URHO3D_HANDLER(ContextMenuUnit, HandleToggledFiedView));
    AddChild(button);
}


void ContextMenuUnit::HandleToggledFiedView(StringHash, VariantMap& eventData)
{
    bool state = (bool)eventData[Toggled::P_STATE].GetBool();

    TheWindowTarget->SetVisible(state);
}

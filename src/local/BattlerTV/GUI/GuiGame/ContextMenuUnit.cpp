// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


ContextMenuUnit::ContextMenuUnit(Context *context) :
    WindowTV(context)
{
    SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("WindowBorder");

    SetLayout(LM_VERTICAL, 3, IntRect(3, 3, 3, 3));
    title = Label::Create("", true, 8);
    title->SetAlignment(HA_CENTER, VA_TOP);
    AddChild(title);
}


void ContextMenuUnit::Create(GameObject *object_)
{
    object = object_;
    title->SetText(object->GetName());

    if(object->GetGameObjectType() == GameObject::Unit)
    {
        CreateForUnit();
    }
}


void ContextMenuUnit::CreateForUnit()
{
    SharedPtr<ButtonToggled> button(new ButtonToggled(nullptr, "Field View", 100));
    SubscribeToEvent(button, E_TOGGLED, URHO3D_HANDLER(ContextMenuUnit, HandleToggledFiedView));
    AddChild(button);
}


void ContextMenuUnit::HandleToggledFiedView(StringHash, VariantMap& eventData) //-V2009
{
    bool state = (bool)eventData[Toggled::P_STATE].GetBool();

    TheWindowTarget->SetVisible(state);

    UnitObject::SetViewTargetView(state);
}

// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/_TButtonSwitch.h"


MenuConfirmExit::MenuConfirmExit(Context *context) : WindowMenu(context)
{
    SET_VERTICAL_LAYOUT_0_6(this);
    SharedPtr<Label> label(Label::Create("Exit in OS?"));
    AddChild(label);

    SharedPtr<UIElement> layer(CreateChild<UIElement>());
    SET_HORIZONTAL_LAYOUT_6_6(layer);
    
    buttonOk = new ButtonTV(layer, "Ok");
    buttonCancel = new ButtonTV(layer, "Cancel");

    SubscribeToEvent(buttonOk, E_RELEASED, URHO3D_HANDLER(MenuConfirmExit, HandleButtonRelease));
    SubscribeToEvent(buttonCancel, E_RELEASED, URHO3D_HANDLER(MenuConfirmExit, HandleButtonRelease));

    AddChild(layer);
}


void MenuConfirmExit::RegisterObject(Context *context)
{
    context->RegisterFactory<MenuConfirmExit>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(TWindow);
}


void MenuConfirmExit::HandleButtonRelease(StringHash, VariantMap& eventData)
{
    Button *button = (Button*)eventData[Released::P_ELEMENT].GetPtr();

    if (button == buttonOk)
    {
        OnPressButtonOk();
    }
    else if (button == buttonCancel)
    {
        OnPressButtonCancel();
    }
}


void MenuConfirmExit::OnPressButtonOk()
{
    VariantMap eventData = GetEventDataMap();
    eventData[MenuEvent::P_TYPE] = MenuEvent_ExitInOS;
    SendEvent(E_MENU, eventData);
}


void MenuConfirmExit::OnPressButtonCancel()
{
    TheMenuConfirmExit->SetVisible(false);
    TheMenuMain->SetVisible(true);
}

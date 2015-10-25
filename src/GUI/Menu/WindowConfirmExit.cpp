#include <stdafx.h>


#include "WindowConfirmExit.h"
#include "GUI/Elements/Button.h"
#include "GUI/Elements/Label.h"
#include "GUI/GUI.h"
#include "GUI/Menu/MenuMain.h"



lWindowConfirmExit::lWindowConfirmExit(Context *) :
    lWindow()
{
    SET_VERTICAL_LAYOUT_0_6(this);
    SharedPtr<lLabel> label(lLabel::Create("Exit in OS?"));
    AddChild(label);

    SharedPtr<UIElement> layer(CreateChild<UIElement>());
    SET_HORIZONTAL_LAYOUT_6_6(layer);
    
    buttonOk = new lButton(layer, "Ok");
    buttonCancel = new lButton(layer, "Cancel");

    SubscribeToEvent(buttonOk, Urho3D::E_RELEASED, HANDLER(lWindowConfirmExit, HandleButtonRelease));
    SubscribeToEvent(buttonCancel, Urho3D::E_RELEASED, HANDLER(lWindowConfirmExit, HandleButtonRelease));

    AddChild(layer);
}

void lWindowConfirmExit::RegisterObject(Context *context)
{
    context->RegisterFactory<lWindowConfirmExit>("UI");

    COPY_BASE_ATTRIBUTES(lWindow);
}

void lWindowConfirmExit::HandleButtonRelease(StringHash, VariantMap& eventData)
{
    Button *button = (Button*)eventData[Urho3D::Released::P_ELEMENT].GetPtr();

    if (button == buttonOk)
    {
        eventData = GetEventDataMap();
        eventData[MenuEvent::P_TYPE] = MenuEvent_ExitInOS;
        SendEvent(E_MENU, eventData);
    }
    else if (button == buttonCancel)
    {
        gWindowConfirmExit->SetVisible(false);
        gMenuMain->SetVisible(true);
    }

    
}
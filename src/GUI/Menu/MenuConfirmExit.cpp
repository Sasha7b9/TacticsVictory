#include <stdafx.h>


#include "MenuConfirmExit.h"
#include "GUI/Elements/Button.h"
#include "GUI/Elements/Label.h"
#include "GUI/GUI.h"
#include "GUI/Menu/MenuMain.h"



lMenuConfirmExit::lMenuConfirmExit(Context *) :
    lWindow()
{
    SetLayout(Urho3D::LM_VERTICAL, 0, IntRect(6, 6, 6, 6));
    SharedPtr<lLabel> label(lLabel::Create("Exit in OS?", 20));
    AddChild(label);

    SharedPtr<UIElement> layer(CreateChild<UIElement>());
    layer->SetLayout(Urho3D::LM_HORIZONTAL, 6, IntRect(6, 6, 6, 6));
    
    buttonOk = new lButton(layer, "Ok");
    buttonCancel = new lButton(layer, "Cancel");

    SubscribeToEvent(buttonOk, Urho3D::E_RELEASED, HANDLER(lMenuConfirmExit, HandleButtonRelease));
    SubscribeToEvent(buttonCancel, Urho3D::E_RELEASED, HANDLER(lMenuConfirmExit, HandleButtonRelease));

    AddChild(layer);
}

void lMenuConfirmExit::RegisterObject(Context *context)
{
    context->RegisterFactory<lMenuConfirmExit>("UI");

    COPY_BASE_ATTRIBUTES(lWindow);
}

void lMenuConfirmExit::HandleButtonRelease(StringHash, VariantMap& eventData)
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
        gMenuConfirmExit->SetVisible(false);
        gMenuMain->SetVisible(true);
    }

    
}
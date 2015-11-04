#include <stdafx.h>


#include "WindowConfirmExit.h"
#include "GUI/Elements/ButtonMain.h"
#include "GUI/Elements/Label.h"
#include "GUI/GUI.h"
#include "GUI/Menu/MenuMain.h"



WindowConfirmExit::WindowConfirmExit(UContext *) :
    lWindow()
{
    SET_VERTICAL_LAYOUT_0_6(this);
    SharedPtr<Label> label(Label::Create("Exit in OS?"));
    AddChild(label);

    SharedPtr<UIElement> layer(CreateChild<UIElement>());
    SET_HORIZONTAL_LAYOUT_6_6(layer);
    
    buttonOk = new ButtonMain(layer, "Ok");
    buttonCancel = new ButtonMain(layer, "Cancel");

    SubscribeToEvent(buttonOk, Urho3D::E_RELEASED, HANDLER(WindowConfirmExit, HandleButtonRelease));
    SubscribeToEvent(buttonCancel, Urho3D::E_RELEASED, HANDLER(WindowConfirmExit, HandleButtonRelease));

    AddChild(layer);
}

void WindowConfirmExit::RegisterObject(UContext *context)
{
    context->RegisterFactory<WindowConfirmExit>("UI");

    COPY_BASE_ATTRIBUTES(lWindow);
}

void WindowConfirmExit::HandleButtonRelease(StringHash, VariantMap& eventData)
{
    UButton *button = (UButton*)eventData[Urho3D::Released::P_ELEMENT].GetPtr();

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
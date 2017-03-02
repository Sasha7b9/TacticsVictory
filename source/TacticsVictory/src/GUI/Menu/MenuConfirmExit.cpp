#include <stdafx.h>
#include "MenuConfirmExit.h"
#include "GUI/Controls/Button.h"
#include "GUI/Controls/Label.h"
#include "GUI/GUI.h"
#include "GUI/Menu/MenuMain.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MenuConfirmExit::MenuConfirmExit(Context *) :
    WindowRTS()
{
    SET_VERTICAL_LAYOUT_0_6(this);
    SharedPtr<Label> label(Label::Create("Exit in OS?"));
    AddChild(label);

    SharedPtr<UIElement> layer(CreateChild<UIElement>());
    SET_HORIZONTAL_LAYOUT_6_6(layer);
    
    buttonOk = new ButtonRTS(layer, "Ok");
    buttonCancel = new ButtonRTS(layer, "Cancel");

    SubscribeToEvent(buttonOk, E_RELEASED, URHO3D_HANDLER(MenuConfirmExit, HandleButtonRelease));
    SubscribeToEvent(buttonCancel, E_RELEASED, URHO3D_HANDLER(MenuConfirmExit, HandleButtonRelease));

    AddChild(layer);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MenuConfirmExit::RegisterObject(Context *context)
{
    context->RegisterFactory<MenuConfirmExit>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(WindowRTS);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MenuConfirmExit::OnPressButtonOk()
{
    VariantMap eventData = GetEventDataMap();
    eventData[MenuEvent::P_TYPE] = MenuEvent_ExitInOS;
    SendEvent(E_MENU, eventData);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MenuConfirmExit::OnPressButtonCancel()
{
    gMenuConfirmExit->SetVisible(false);
    gMenuMain->SetVisible(true);
}

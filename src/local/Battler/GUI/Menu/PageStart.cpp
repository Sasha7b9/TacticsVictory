// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/Buttons/ButtonSwitch_.h"
#include "GUI/Menu/Menu.h"
#include "GUI/Menu/PageStart.h"


MenuStart::MenuStart() : MenuPage()
{
    SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));

    SetName("Start menu");

    SharedPtr<Label> text(Label::Create("Tactics Victory", true, 20, 120, -1));
    text->SetTextAlignment(HA_CENTER);
    AddChild(text);

    buttonPlay = new ButtonT(this, "Play");
    buttonPlay->SetVar(VAR_MENU_EVENT, Variant(ME_OPEN_PLAY));

    buttonOptions = new ButtonT(this, "Options");
    buttonOptions->SetVar(VAR_MENU_EVENT, Variant(ME_OPEN_OPTIONS));

    buttonExit = new ButtonT(this, "Exit");

    buttons.Push(buttonPlay);
    buttons.Push(buttonOptions);
    buttons.Push(buttonExit);

    SubscribeToEvent(buttonPlay, E_RELEASED, URHO3D_HANDLER(MenuStart, HandleButtonRelease));
    SubscribeToEvent(buttonOptions, E_RELEASED, URHO3D_HANDLER(MenuStart, HandleButtonRelease));
    SubscribeToEvent(buttonExit, E_RELEASED, URHO3D_HANDLER(MenuStart, HandleButtonRelease));
}


MenuStart::~MenuStart()
{
}


void MenuStart::HandleButtonRelease(StringHash, VariantMap& eventData)
{
    if(!TheMenu->IsActive())
    {
        return;
    }

    using namespace Released;
    using namespace MenuEvent;

    Button *button = dynamic_cast<Button*>(eventData[P_ELEMENT].GetPtr());

    const Variant &value = button->GetVar(VAR_MENU_EVENT); //-V522

    if(!value.IsEmpty())
    {
        eventData = GetEventDataMap();
        eventData[P_SOURCE] = this;
        eventData[P_TYPE] = value.GetUInt();

        if(value == ME_START_SERVER)
        {
//            eventData[P_PORT] = SERVER_PORT;
        }

        SendEvent(E_MENU, eventData);
    }
    else if (button == buttonExit)
    {
        TheEngine->Exit();
    }
}


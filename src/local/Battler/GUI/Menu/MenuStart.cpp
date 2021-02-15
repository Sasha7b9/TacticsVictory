// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "MenuStart.h"
#include "MenuAboutMe.h"
#include "MenuEvents.h"
#include "MenuRTS.h"
#include "GlobalFunctions.h"
#include "TacticsVictory.h"



#define VAR_MENU_EVENT "VAR_MENU_EVENT"




MenuStart::MenuStart(Context *context) : WindowMenu(context)
{
    SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    SetName("Start menu");

    SharedPtr<Label> text(Label::Create("Tactics Victory", true, 20, 120, -1));
    AddChild(text);

    buttonLanguage = new ButtonSwitch(this, "Language : EN");
    buttonLanguage->AddState("Language : RU");
    buttonLanguage->SetState((uint)TheSet->GetInt(TV_LANGUAGE));

    buttonServer = new ButtonRTS(this, "Server");
    buttonServer->SetVar(VAR_MENU_EVENT, Variant(MenuEvent_StartServer));

    buttonClient = new ButtonRTS(this, "Client");
    buttonClient->SetVar(VAR_MENU_EVENT, Variant(MenuEvent_StartClient));

    buttonEditor = new ButtonRTS(this, "Editor");

    buttonOptions = new ButtonRTS(this, "Options");
    buttonOptions->SetVar(VAR_MENU_EVENT, Variant(MenuEvent_OpenOptions));

    buttonHelp = new ButtonRTS(this, "Help");

    buttonAboutGame = new ButtonRTS(this, "About game");

    buttonAboutMe = new ButtonRTS(this, "About me");
    buttonAboutMe->SetVar(VAR_MENU_EVENT, Variant(MenuEvent_OpenAboutMe));

    buttonExit = new ButtonRTS(this, "Exit");

    buttons.Push(buttonLanguage);
    buttons.Push(buttonServer);
    buttons.Push(buttonClient);
    buttons.Push(buttonEditor);
    buttons.Push(buttonOptions);
    buttons.Push(buttonHelp);
    buttons.Push(buttonAboutGame);
    buttons.Push(buttonAboutMe);
    buttons.Push(buttonExit);

    SubscribeToEvent(buttonLanguage, E_RELEASED, URHO3D_HANDLER(MenuStart, HandleButtonRelease));
    SubscribeToEvent(buttonServer, E_RELEASED, URHO3D_HANDLER(MenuStart, HandleButtonRelease));
    SubscribeToEvent(buttonClient, E_RELEASED, URHO3D_HANDLER(MenuStart, HandleButtonRelease));
    SubscribeToEvent(buttonEditor, E_RELEASED, URHO3D_HANDLER(MenuStart, HandleButtonRelease));
    SubscribeToEvent(buttonOptions, E_RELEASED, URHO3D_HANDLER(MenuStart, HandleButtonRelease));
    SubscribeToEvent(buttonHelp, E_RELEASED, URHO3D_HANDLER(MenuStart, HandleButtonRelease));
    SubscribeToEvent(buttonAboutGame, E_RELEASED, URHO3D_HANDLER(MenuStart, HandleButtonRelease));
    SubscribeToEvent(buttonAboutMe, E_RELEASED, URHO3D_HANDLER(MenuStart, HandleButtonRelease));
    SubscribeToEvent(buttonExit, E_RELEASED, URHO3D_HANDLER(MenuStart, HandleButtonRelease));
}


MenuStart::~MenuStart()
{
}


void MenuStart::HandleButtonRelease(StringHash, VariantMap& eventData)
{
    if(!gMenu->IsActive())
    {
        return;
    }

    using namespace Released;
    using namespace MenuEvent;

    Button *button = dynamic_cast<Button*>(eventData[P_ELEMENT].GetPtr());

    const Variant &value = button->GetVar(VAR_MENU_EVENT);
    if(!value.IsEmpty())
    {
        eventData = GetEventDataMap();
        eventData[P_SOURCE] = this;
        eventData[P_TYPE] = value.GetUInt();
        if(value == MenuEvent_StartServer)
        {
            eventData[P_PORT] = SERVER_PORT;
        }
        SendEvent(E_MENU, eventData);
    }
    else if (button == buttonLanguage)
    {
        TheLocalization->SetLanguage(buttonLanguage->GetState() == 0 ? "en" : "ru");
        TheSet->SetInt(TV_LANGUAGE, static_cast<int>(buttonLanguage->GetState()));
    }
    else if (button == buttonExit)
    {
        TheEngine->Exit();
    }
}


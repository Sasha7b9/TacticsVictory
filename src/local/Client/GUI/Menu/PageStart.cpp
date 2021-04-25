// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Client.h"
#include "FileSystem/ConfigurationFile_v.h"
#include "GUI/Controls/Buttons/ButtonSwitch_.h"
#include "GUI/Menu/Menu.h"
#include "GUI/Menu/MenuEvents_.h"
#include "GUI/Menu/PageStart.h"


PageStart::PageStart() : MenuPage()
{
    SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));

    SetName("Start menu");

    SharedPtr<Label> text(Label::Create("Tactics Victory", 20, 120, -1));
    text->SetAlignment(HA_CENTER, VA_CENTER);
    text->SetTextAlignment(HA_CENTER);
    AddChild(text);

    buttonLanguage = new ButtonSwitch(this, "Language : EN");
    buttonLanguage->AddState("Language : RU");
    buttonLanguage->SetState((uint)TheSettings.GetInt("language"));

    buttonPlay = new ButtonT(this, "Play");
    buttonPlay->SetVar(VAR_MENU_EVENT, Variant(ME_OPEN_PLAY));

    buttonEditor = new ButtonT(this, "Editor");

    buttonOptions = new ButtonT(this, "Options");
    buttonOptions->SetVar(VAR_MENU_EVENT, Variant(ME_OPEN_OPTIONS));

    buttonAboutGame = new ButtonT(this, "About game");

    buttonAboutMe = new ButtonT(this, "About me");
    buttonAboutMe->SetVar(VAR_MENU_EVENT, Variant(ME_OPEN_ABOUT_ME));

    buttonExit = new ButtonT(this, "Exit");

    buttons.Push(buttonLanguage);
    buttons.Push(buttonPlay);
    buttons.Push(buttonEditor);
    buttons.Push(buttonOptions);
    buttons.Push(buttonAboutGame);
    buttons.Push(buttonAboutMe);
    buttons.Push(buttonExit);

    SubscribeToEvent(buttonLanguage, E_RELEASED, URHO3D_HANDLER(PageStart, HandleButtonRelease));
    SubscribeToEvent(buttonPlay, E_RELEASED, URHO3D_HANDLER(PageStart, HandleButtonRelease));
    SubscribeToEvent(buttonEditor, E_RELEASED, URHO3D_HANDLER(PageStart, HandleButtonRelease));
    SubscribeToEvent(buttonOptions, E_RELEASED, URHO3D_HANDLER(PageStart, HandleButtonRelease));
    SubscribeToEvent(buttonAboutGame, E_RELEASED, URHO3D_HANDLER(PageStart, HandleButtonRelease));
    SubscribeToEvent(buttonAboutMe, E_RELEASED, URHO3D_HANDLER(PageStart, HandleButtonRelease));
    SubscribeToEvent(buttonExit, E_RELEASED, URHO3D_HANDLER(PageStart, HandleButtonRelease));
}


PageStart::~PageStart()
{
}


void PageStart::HandleButtonRelease(StringHash, VariantMap& eventData)
{
    if(!TheMenu->IsActive())
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

        if(value == ME_START_SERVER)
        {
//            eventData[P_PORT] = SERVER_PORT;
        }

        SendEvent(E_MENU, eventData);
    }
    else if (button == buttonLanguage)
    {
        TheLocalization->SetLanguage(buttonLanguage->GetState() == 0 ? "en" : "ru");
        TheSettings.SetInt((int)buttonLanguage->GetState(), "language");
        TheClient->SetWindowTitleAndIcon();
    }
    else if (button == buttonEditor)
    {
        int result = system("start Editor.exe");
        (void)result;
        TheEngine->Exit();
    }
    else if (button == buttonExit)
    {
        TheEngine->Exit();
    }
}


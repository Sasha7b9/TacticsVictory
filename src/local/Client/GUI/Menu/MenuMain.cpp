// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/Buttons/ButtonSwitch_.h"
#include "GUI/Menu/Menu.h"
#include "GUI/Menu/MenuMain.h"


MenuMain::MenuMain() : WindowMenu()
{
    SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));

    SetName("Start menu");

    SharedPtr<Label> text(Label::Create("Tactics Victory", true, 20, 120, -1));
    text->SetTextAlignment(HA_CENTER);
    AddChild(text);

    buttonLanguage = new ButtonSwitch(this, "Language : EN");
    buttonLanguage->AddState("Language : RU");
    buttonLanguage->SetState((uint)TheSet->GetInt(TV_LANGUAGE));

    buttonPlay = new ButtonT(this, "Play");
    buttonPlay->SetVar(VAR_MENU_EVENT, Variant(ME_OPEN_PLAY));

    buttonEditor = new ButtonT(this, "Editor");

    buttonAboutGame = new ButtonT(this, "About game");

    buttonAboutMe = new ButtonT(this, "About me");
    buttonAboutMe->SetVar(VAR_MENU_EVENT, Variant(ME_OPEN_ABOUT_ME));

    buttonExit = new ButtonT(this, "Exit");

    buttons.Push(buttonLanguage);
    buttons.Push(buttonPlay);
    buttons.Push(buttonEditor);
    buttons.Push(buttonAboutGame);
    buttons.Push(buttonAboutMe);
    buttons.Push(buttonExit);

    SubscribeToEvent(buttonLanguage, E_RELEASED, URHO3D_HANDLER(MenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonPlay, E_RELEASED, URHO3D_HANDLER(MenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonEditor, E_RELEASED, URHO3D_HANDLER(MenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonAboutGame, E_RELEASED, URHO3D_HANDLER(MenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonAboutMe, E_RELEASED, URHO3D_HANDLER(MenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonExit, E_RELEASED, URHO3D_HANDLER(MenuMain, HandleButtonRelease));
}


MenuMain::~MenuMain()
{
}


void MenuMain::HandleButtonRelease(StringHash, VariantMap& eventData)
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
    else if (button == buttonLanguage)
    {
        TheLocalization->SetLanguage(buttonLanguage->GetState() == 0 ? "en" : "ru");
        TheSet->SetInt(TV_LANGUAGE, static_cast<int>(buttonLanguage->GetState()));
    }
    else if (button == buttonEditor)
    {
        system("start Editor.exe");
        TheEngine->Exit();
    }
    else if (button == buttonExit)
    {
        TheEngine->Exit();
    }
}


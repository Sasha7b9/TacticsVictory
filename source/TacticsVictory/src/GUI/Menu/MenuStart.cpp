#include <stdafx.h>
#include "MenuStart.h"
#include "MenuAboutMe.h"
#include "MenuEvents.h"
#include "MenuRTS.h"
#include "GlobalFunctions.h"
#include "TacticsVictory.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MenuStart::MenuStart(Context *context) : WindowMenu(context)
{
    SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    SetName("Start menu");

    SharedPtr<Label> text(Label::Create("Tactics Victory", true, 20, 120, -1));
    AddChild(text);

    buttonLanguage = new ButtonSwitch(this, "Language : EN");
    buttonLanguage->AddState("Language : RU");
    buttonLanguage->SetState((uint)gSet->GetInt(TV_LANGUAGE));
    buttonServer = new ButtonRTS(this, "Server");
    buttonClient = new ButtonRTS(this, "Client");
    buttonEditor = new ButtonRTS(this, "Editor");
    buttonOptions = new ButtonRTS(this, "Options");
    buttonHelp = new ButtonRTS(this, "Help");
    buttonAboutGame = new ButtonRTS(this, "About game");
    buttonAboutMe = new ButtonRTS(this, "About me");
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
MenuStart::~MenuStart()
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MenuStart::HandleButtonRelease(StringHash, VariantMap& eventData)
{
    using namespace Released;

    Button *button = (Button*)eventData[P_ELEMENT].GetPtr();

    if (button == buttonLanguage)
    {
        gLocalization->SetLanguage(buttonLanguage->GetState() == 0 ? "en" : "ru");
        gSet->SetInt(TV_LANGUAGE, (int)buttonLanguage->GetState());
    }
    if(button == buttonServer)
    {
        SetDisabled();
        gTacticsVictory->CreateNewGame();
    }
    else if(button == buttonClient)
    {

    }
    else if(button == buttonEditor)
    {

    }
    else if (button == buttonOptions)
    {

    }
    else if (button == buttonHelp)
    {

    }
    else if (button == buttonAboutGame)
    {

    }
    else if (button == buttonAboutMe)
    {
        gMenu->Open(gMenu->menuAbout);
    }
    else if (button == buttonExit)
    {
        gEngine->Exit();
    }
}


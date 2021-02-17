// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


MenuGame::MenuGame(Context *) : WindowMenu()
{
    SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    SetName("Main menu");

    SharedPtr<Label> text(Label::Create("Tactics Victory", true, 20, -1, -1));
    AddChild(text);
    
    buttonNewGame  = new ButtonTV(this, "New game");
    buttonEditor = new ButtonTV(this, "Editor");
    buttonOptions = new ButtonTV(this, "Options");
    buttonLanguage = new ButtonSwitch(this, "Language : EN");
    buttonLanguage->AddState("Language : RU");
    buttonLanguage->SetState((uint)TheSet->GetInt(TV_LANGUAGE));
    buttonExit = new ButtonTV(this, "Exit");
    buttonCancel = new ButtonTV(this, "Cancel");

    buttons.Push(buttonNewGame);
    buttons.Push(buttonEditor);
    buttons.Push(buttonOptions);
    buttons.Push(buttonLanguage);
    buttons.Push(buttonExit);
    buttons.Push(buttonCancel);

    SubscribeToEvent(buttonOptions, E_RELEASED, URHO3D_HANDLER(MenuGame, HandleButtonRelease));
    SubscribeToEvent(buttonEditor, E_RELEASED, URHO3D_HANDLER(MenuGame, HandleButtonRelease));
    SubscribeToEvent(buttonNewGame, E_RELEASED, URHO3D_HANDLER(MenuGame, HandleButtonRelease));
    SubscribeToEvent(buttonExit, E_RELEASED, URHO3D_HANDLER(MenuGame, HandleButtonRelease));
    SubscribeToEvent(buttonLanguage, E_RELEASED, URHO3D_HANDLER(MenuGame, HandleButtonRelease));
    SubscribeToEvent(buttonCancel, E_RELEASED, URHO3D_HANDLER(MenuGame, HandleButtonRelease));

    text->SetWidth(GetWidth());

    mapButtonsActions[buttonOptions] = MenuEvent_OpenOptions;
    mapButtonsActions[buttonEditor] = MenuEvent_OpenEditor;
    mapButtonsActions[buttonExit] = MenuEvent_ExitInOS;
}


void MenuGame::RegisterObject(Context* context)
{
    context->RegisterFactory<MenuGame>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(WindowMenu);
}


void MenuGame::HandleButtonRelease(StringHash, VariantMap& eventData)
{
    Button *button = (Button*)eventData[Released::P_ELEMENT].GetPtr();

    if (button == buttonExit)
    {
        TheEngine->Exit();
        TheMenuMain->SetDisabled();
    
    }
    else if (button == buttonLanguage)
    {
        TheLocalization->SetLanguage(buttonLanguage->GetState() == 0 ? "en" : "ru");
        TheSet->SetInt(TV_LANGUAGE, (int)buttonLanguage->GetState());
    }
    else if (button == buttonOptions)
    {
        eventData = GetEventDataMap();
        eventData[MenuEvent::P_TYPE] = mapButtonsActions[button];
        SendEvent(E_MENU, eventData);
    }
    else if (button == buttonNewGame)
    {
        buttonExit->SetText("Exit from game");
    }
    else if (button == buttonCancel)
    {
        TheMenuMain->Close();
    }
}


void MenuGame::Open()
{
    TheScene->scene->SetTimeScale(0.0f);
    TheCamera->SetEnabled(false);
}


void MenuGame::Close()
{
    TheScene->scene->SetTimeScale(1.0f);
    TheCamera->SetEnabled(true);
}

// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/Buttons/ButtonSwitch_.h"
#include "GUI/Menu/MenuMain.h"
#include "Scene/SceneC.h"
#include "Scene/Cameras/Camera.h"


MenuMain::MenuMain(Context *) : WindowMenu()
{
    SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    SetName("Main menu");

    SharedPtr<Label> text(Label::Create("Tactics Victory", true, 20, -1, -1));
    AddChild(text);
    
    buttonNewGame  = new ButtonT(this, "New game");
    buttonEditor = new ButtonT(this, "Editor");
    buttonLanguage = new ButtonSwitch(this, "Language : EN");
    buttonLanguage->AddState("Language : RU");
    buttonLanguage->SetState((uint)TheSet->GetInt(TV_LANGUAGE));
    buttonExit = new ButtonT(this, "Exit");
    buttonCancel = new ButtonT(this, "Cancel");

    buttons.Push(buttonNewGame);
    buttons.Push(buttonEditor);
    buttons.Push(buttonLanguage);
    buttons.Push(buttonExit);
    buttons.Push(buttonCancel);

    SubscribeToEvent(buttonEditor, E_RELEASED, URHO3D_HANDLER(MenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonNewGame, E_RELEASED, URHO3D_HANDLER(MenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonExit, E_RELEASED, URHO3D_HANDLER(MenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonLanguage, E_RELEASED, URHO3D_HANDLER(MenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonCancel, E_RELEASED, URHO3D_HANDLER(MenuMain, HandleButtonRelease));

    text->SetWidth(GetWidth());

    mapButtonsActions[buttonEditor] = ME_OPEN_EDITOR;
    mapButtonsActions[buttonExit] = ME_EXIT_IN_OS;
}


void MenuMain::RegisterObject()
{
    Context *context = TheContext;

    context->RegisterFactory<MenuMain>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(WindowMenu);
}


void MenuMain::HandleButtonRelease(StringHash, VariantMap& eventData)
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
    else if (button == buttonNewGame)
    {
        buttonExit->SetText("Exit from game");
    }
    else if (button == buttonCancel)
    {
        TheMenuMain->Close();
    }
}


void MenuMain::Open()
{
    TheScene->SetTimeScale(0.0f);
    TheCamera->SetEnabled(false);
}


void MenuMain::Close()
{
    TheScene->SetTimeScale(1.0f);
    TheCamera->SetEnabled(true);
}

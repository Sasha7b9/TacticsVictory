// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/Buttons/ButtonSwitch_.h"
#include "GUI/Menu/MenuGame.h"
#include "Scene/SceneC.h"
#include "Scene/Cameras/Camera.h"


MenuGame::MenuGame(Context *) : WindowMenu()
{
    SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    SetName("Main menu");

    SharedPtr<Label> text(Label::Create("Tactics Victory", true, 20, -1, -1));
    AddChild(text);
    
    buttonNewGame  = new ButtonT(this, "New game");
    buttonOptions = new ButtonT(this, "Options");
    buttonExit = new ButtonT(this, "Exit");
    buttonCancel = new ButtonT(this, "Cancel");

    buttons.Push(buttonNewGame);
    buttons.Push(buttonOptions);
    buttons.Push(buttonExit);
    buttons.Push(buttonCancel);

    SubscribeToEvent(buttonOptions, E_RELEASED, URHO3D_HANDLER(MenuGame, HandleButtonRelease));
    SubscribeToEvent(buttonNewGame, E_RELEASED, URHO3D_HANDLER(MenuGame, HandleButtonRelease));
    SubscribeToEvent(buttonExit, E_RELEASED, URHO3D_HANDLER(MenuGame, HandleButtonRelease));
    SubscribeToEvent(buttonCancel, E_RELEASED, URHO3D_HANDLER(MenuGame, HandleButtonRelease));

    text->SetWidth(GetWidth());

    mapButtonsActions[buttonOptions] = ME_OPEN_OPTIONS;
    mapButtonsActions[buttonExit] = ME_EXIT_IN_OS;
}


void MenuGame::RegisterObject()
{
    Context *context = TheContext;

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
    TheScene->SetTimeScale(0.0f);
    TheCamera->SetEnabled(false);
}


void MenuGame::Close()
{
    TheScene->SetTimeScale(1.0f);
    TheCamera->SetEnabled(true);
}

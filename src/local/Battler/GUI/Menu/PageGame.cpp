// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/Buttons/ButtonSwitch_.h"
#include "GUI/Menu/PageGame.h"
#include "Scene/SceneC.h"
#include "Scene/Cameras/Camera.h"


PageGame::PageGame(Context *) : MenuPage()
{
    SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    SetName("Main menu");

    SharedPtr<Label> text(Label::Create("Tactics Victory", 20, -1, -1));
    text->SetAlignment(HA_CENTER, VA_CENTER);
    AddChild(text);
    
    buttonNewGame  = new ButtonT(this, "New game");
    buttonOptions = new ButtonT(this, "Options");
    buttonExit = new ButtonT(this, "Exit");
    buttonCancel = new ButtonT(this, "Cancel");

    buttons.Push(buttonNewGame);
    buttons.Push(buttonOptions);
    buttons.Push(buttonExit);
    buttons.Push(buttonCancel);

    SubscribeToEvent(buttonOptions, E_RELEASED, URHO3D_HANDLER(PageGame, HandleButtonRelease));
    SubscribeToEvent(buttonNewGame, E_RELEASED, URHO3D_HANDLER(PageGame, HandleButtonRelease));
    SubscribeToEvent(buttonExit, E_RELEASED, URHO3D_HANDLER(PageGame, HandleButtonRelease));
    SubscribeToEvent(buttonCancel, E_RELEASED, URHO3D_HANDLER(PageGame, HandleButtonRelease));

    text->SetWidth(GetWidth());

    mapButtonsActions[buttonOptions] = ME_OPEN_OPTIONS;
    mapButtonsActions[buttonExit] = ME_EXIT_IN_OS;
}


void PageGame::RegisterObject()
{
    Context *context = TheContext;

    context->RegisterFactory<PageGame>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(MenuPage);
}


void PageGame::HandleButtonRelease(StringHash, VariantMap& eventData)
{
    Button *button = (Button*)eventData[Released::P_ELEMENT].GetPtr();

    if (button == buttonExit)
    {
        TheEngine->Exit();
        ThePageGame->SetDisabled();
    
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
        ThePageGame->Close();
    }
}


void PageGame::Open()
{
    TheScene->SetTimeScale(0.0f);
    TheCamera->SetEnabled(false);
}


void PageGame::Close()
{
    TheScene->SetTimeScale(1.0f);
    TheCamera->SetEnabled(true);
}

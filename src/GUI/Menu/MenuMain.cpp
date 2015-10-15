#include <stdafx.h>


tvMenuMain::tvMenuMain(Context *context) :
    tvWindow(context)
{
    SetLayout(Urho3D::LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    SetName("Main menu");

    SharedPtr<tvLabel> text(tvLabel::Create("Tactics Victory", 20));
    AddChild(text);

    SharedPtr<Button> btnTest(new Button(gContext));
    btnTest->SetStyleAuto();
    btnTest->SetFixedSize(50, 20);
    AddChild(btnTest);

    buttonNewGame  = new tvButton(0, "New game");
    AddChild(buttonNewGame);
    buttonEditor = new tvButton(this, "Editor");
    buttonOptions = new tvButton(this, "Options");
    buttonExit = new tvButton(this, "Exit");
    SubscribeToEvent(buttonOptions, E_RELEASED, HANDLER(tvMenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonOptions, E_HOVERBEGIN, HANDLER(tvMenuMain, HandleHoverBegin));
    SubscribeToEvent(buttonOptions, E_HOVEREND, HANDLER(tvMenuMain, HandleHoverEnd));

    SubscribeToEvent(buttonEditor, E_RELEASED, HANDLER(tvMenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonEditor, E_HOVERBEGIN, HANDLER(tvMenuMain, HandleHoverBegin));
    SubscribeToEvent(buttonEditor, E_HOVEREND, HANDLER(tvMenuMain, HandleHoverEnd));

    SubscribeToEvent(buttonNewGame, E_RELEASED, HANDLER(tvMenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonNewGame, E_HOVERBEGIN, HANDLER(tvMenuMain, HandleHoverBegin));
    SubscribeToEvent(buttonNewGame, E_HOVEREND, HANDLER(tvMenuMain, HandleHoverEnd));

    SubscribeToEvent(buttonExit, E_RELEASED, HANDLER(tvMenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonExit, E_HOVERBEGIN, HANDLER(tvMenuMain, HandleHoverBegin));
    SubscribeToEvent(buttonExit, E_HOVEREND, HANDLER(tvMenuMain, HandleHoverEnd));

    text->SetWidth(GetWidth());

    mapButtonsActions[buttonNewGame] = MenuEvent_NewGame;
    mapButtonsActions[buttonOptions] = MenuEvent_MenuOptionsOpen;
    mapButtonsActions[buttonEditor] = MenuEvent_OpenEditor;
    mapButtonsActions[buttonExit] = MenuEvent_ExitInOS;
}

void tvMenuMain::RegisterObject(Context* context)
{
    context->RegisterFactory<tvMenuMain>("UI");

    COPY_BASE_ATTRIBUTES(tvWindow);
}

void tvMenuMain::HandleButtonRelease(StringHash, VariantMap& eventData)
{
    Button *button = (Button*)eventData[Urho3D::Released::P_ELEMENT].GetPtr();
    eventData = GetEventDataMap();
    eventData[MenuEvent::P_TYPE] = mapButtonsActions[button];
    SendEvent(E_MENU, eventData);

    if(button == buttonNewGame)
    {
        buttonExit->SetText("Exit from game");
    }
}

void tvMenuMain::HandleHoverBegin(StringHash, VariantMap&)
{
    gCursor->SetSelected();
}

void tvMenuMain::HandleHoverEnd(StringHash, VariantMap&)
{
    gCursor->SetNormal();
}
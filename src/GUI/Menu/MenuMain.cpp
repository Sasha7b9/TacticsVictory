#include <stdafx.h>


#include "MenuMain.h"
#include "GUI/GUI.h"
#include "GUI/Elements/Button.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/Elements/Label.h"


vMenuMain::vMenuMain(Context *context) :
    vWindow(context)
{
    SetLayout(Urho3D::LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    SetName("Main menu");

    SharedPtr<vLabel> text(vLabel::Create("Tactics Victory", 20));
    AddChild(text);
    
    buttonNewGame  = new vButton(0, "New game");
    AddChild(buttonNewGame);
    buttonEditor = new vButton(this, "Editor");
    buttonOptions = new vButton(this, "Options");
    buttonExit = new vButton(this, "Exit");
    SubscribeToEvent(buttonOptions, E_RELEASED, HANDLER(vMenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonOptions, E_HOVERBEGIN, HANDLER(vMenuMain, HandleHoverBegin));
    SubscribeToEvent(buttonOptions, E_HOVEREND, HANDLER(vMenuMain, HandleHoverEnd));

    SubscribeToEvent(buttonEditor, E_RELEASED, HANDLER(vMenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonEditor, E_HOVERBEGIN, HANDLER(vMenuMain, HandleHoverBegin));
    SubscribeToEvent(buttonEditor, E_HOVEREND, HANDLER(vMenuMain, HandleHoverEnd));

    SubscribeToEvent(buttonNewGame, E_RELEASED, HANDLER(vMenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonNewGame, E_HOVERBEGIN, HANDLER(vMenuMain, HandleHoverBegin));
    SubscribeToEvent(buttonNewGame, E_HOVEREND, HANDLER(vMenuMain, HandleHoverEnd));

    SubscribeToEvent(buttonExit, E_RELEASED, HANDLER(vMenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonExit, E_HOVERBEGIN, HANDLER(vMenuMain, HandleHoverBegin));
    SubscribeToEvent(buttonExit, E_HOVEREND, HANDLER(vMenuMain, HandleHoverEnd));

    text->SetWidth(GetWidth());

    mapButtonsActions[buttonNewGame] = MenuEvent_NewGame;
    mapButtonsActions[buttonOptions] = MenuEvent_MenuOptionsOpen;
    mapButtonsActions[buttonEditor] = MenuEvent_OpenEditor;
    mapButtonsActions[buttonExit] = MenuEvent_ExitInOS;
}

void vMenuMain::RegisterObject(Context* context)
{
    context->RegisterFactory<vMenuMain>("UI");

    COPY_BASE_ATTRIBUTES(vWindow);
}

void vMenuMain::HandleButtonRelease(StringHash, VariantMap& eventData)
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

void vMenuMain::HandleHoverBegin(StringHash, VariantMap&)
{
    gCursor->SetSelected();
}

void vMenuMain::HandleHoverEnd(StringHash, VariantMap&)
{
    gCursor->SetNormal();
}
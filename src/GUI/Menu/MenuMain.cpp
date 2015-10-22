#include <stdafx.h>


#include "MenuMain.h"
#include "GUI/GUI.h"
#include "GUI/Elements/Button.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/Elements/Label.h"
#include "GUI/Menu/MenuConfirmExit.h"


lMenuMain::lMenuMain(Context *) :
    lWindow()
{
    SetLayout(Urho3D::LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    SetName("Main menu");

    SharedPtr<lLabel> text(lLabel::Create("Tactics Victory", 20));
    AddChild(text);
    
    buttonNewGame  = new lButton(0, "New game");
    AddChild(buttonNewGame);
    buttonEditor = new lButton(this, "Editor");
    buttonOptions = new lButton(this, "Options");
    buttonExit = new lButton(this, "Exit");
    SubscribeToEvent(buttonOptions, Urho3D::E_RELEASED, HANDLER(lMenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonEditor, Urho3D::E_RELEASED, HANDLER(lMenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonNewGame, Urho3D::E_RELEASED, HANDLER(lMenuMain, HandleButtonRelease));
    SubscribeToEvent(buttonExit, Urho3D::E_RELEASED, HANDLER(lMenuMain, HandleButtonRelease));

    text->SetWidth(GetWidth());

    mapButtonsActions[buttonNewGame] = MenuEvent_NewGame;
    mapButtonsActions[buttonOptions] = MenuEvent_MenuOptionsOpen;
    mapButtonsActions[buttonEditor] = MenuEvent_OpenEditor;
    mapButtonsActions[buttonExit] = MenuEvent_ExitInOS;
}

void lMenuMain::RegisterObject(Context* context)
{
    context->RegisterFactory<lMenuMain>("UI");

    COPY_BASE_ATTRIBUTES(lWindow);
}

void lMenuMain::HandleButtonRelease(StringHash, VariantMap& eventData)
{
    Button *button = (Button*)eventData[Urho3D::Released::P_ELEMENT].GetPtr();

    if (button == buttonExit)
    {
        gMenuMain->SetVisible(false);
        gGUI->SetVisibleMenu(gMenuConfirmExit, true);
    }
    else
    {
        eventData = GetEventDataMap();
        eventData[MenuEvent::P_TYPE] = mapButtonsActions[button];
        SendEvent(E_MENU, eventData);

        if (button == buttonNewGame)
        {
            buttonExit->SetText("Exit from game");
        }
    }
}

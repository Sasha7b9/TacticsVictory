#include <stdafx.h>
#include "StartMenu.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StartMenu::StartMenu(Context *context) : WindowRTS(context)
{
    SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    SetName("Start menu");

    SharedPtr<Label> text(Label::Create("Tactics Victory", 20, 200, -1));
    AddChild(text);

    buttonStartServer = new ButtonRTS(this, "Start server");
    buttonStartClient = new ButtonRTS(this, "Start client");
    buttonStartEditor = new ButtonRTS(this, "Start editor");

    buttons.Push(buttonStartServer);
    buttons.Push(buttonStartClient);
    buttons.Push(buttonStartEditor);

    SubscribeToEvent(buttonStartServer, E_RELEASED, URHO3D_HANDLER(StartMenu, HandleButtonRelease));
    SubscribeToEvent(buttonStartClient, E_RELEASED, URHO3D_HANDLER(StartMenu, HandleButtonRelease));
    SubscribeToEvent(buttonStartEditor, E_RELEASED, URHO3D_HANDLER(StartMenu, HandleButtonRelease));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void StartMenu::HandleButtonRelease(StringHash, VariantMap&)
{

}

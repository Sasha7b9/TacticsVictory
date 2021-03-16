// 2021/03/16 21:49:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Menu/MenuStart/MenuPlay/MenuPlay.h"
#include "Utils/SettingsTypes.h"


MenuPlay::MenuPlay() : WindowMenu()
{
    SET_VERTICAL_LAYOUT_0_6(this);
    SetName("Play menu");

    SharedPtr<Label> text(Label::Create("Play", true, 20, 120, -1));
    text->SetTextAlignment(HA_CENTER);
    AddChild(text);

    buttonBack = new ButtonT(this, "Back");
    SubscribeToEvent(buttonBack, E_RELEASED, URHO3D_HANDLER(MenuPlay, HandleButtonRelease));
}


void MenuPlay::HandleButtonRelease(StringHash, VariantMap &eventData)
{
    using namespace Released;

    Button *button = (Button *)(eventData[P_ELEMENT].GetPtr());

    if (button == buttonBack)
    {
        SendEventClose();
    }
}

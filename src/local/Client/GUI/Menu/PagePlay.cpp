// 2021/03/16 21:49:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Menu/MenuEvents_.h"
#include "GUI/Menu/PagePlay.h"


PagePlay::PagePlay() : MenuPage()
{
    SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));
    SetName("Play menu");

    SharedPtr<Label> text(Label::Create("Play", 20, 120, -1));
    text->SetAlignment(HA_CENTER, VA_CENTER);
    text->SetTextAlignment(HA_CENTER);
    AddChild(text);

    buttonFindServer = new ButtonT(this, "Find server");
    buttonFindServer->SetVar(VAR_MENU_EVENT, Variant(ME_OPEN_FIND_SERVER));
    buttonCreateServer = new ButtonT(this, "Create server");
    buttonBack = new ButtonT(this, "Back");

    SubscribeToEvent(buttonBack, E_RELEASED, URHO3D_HANDLER(PagePlay, HandleButtonRelease));
    SubscribeToEvent(buttonFindServer, E_RELEASED, URHO3D_HANDLER(PagePlay, HandleButtonRelease));
}


void PagePlay::HandleButtonRelease(StringHash, VariantMap &eventData)
{
    using namespace Released;
    using namespace MenuEvent;

    Button *button = (Button *)(eventData[P_ELEMENT].GetPtr());

    const Variant &value = button->GetVar(VAR_MENU_EVENT);

    if (!value.IsEmpty())
    {
        eventData = GetEventDataMap();
        eventData[P_SOURCE] = this;
        eventData[P_TYPE] = value.GetUInt();
        SendEvent(E_MENU, eventData);
    }
    else if (button == buttonBack)
    {
        SendEventClose();
    }
}

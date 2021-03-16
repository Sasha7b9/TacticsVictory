// 2021/03/16 21:49:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Menu/MenuStart/MenuPlay/MenuPlay.h"
#include "Utils/SettingsTypes.h"


MenuPlay::MenuPlay() : WindowMenu()
{
    SET_VERTICAL_LAYOUT_0_6(this);
    SetName("Play menu");

    SharedPtr<Label> label(Label::Create("Play", true, 20));
    AddChild(label);


    SharedPtr<UIElement> layout(CreateChild<UIElement>());
    layout->SetAlignment(HA_CENTER, VA_TOP);

    buttonBack = new ButtonT(0, "Back", 100);
    SubscribeToEvent(buttonBack, E_RELEASED, URHO3D_HANDLER(MenuPlay, HandleButtonRelease));
    layout->AddChild(buttonBack);
    AddChild(layout);
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

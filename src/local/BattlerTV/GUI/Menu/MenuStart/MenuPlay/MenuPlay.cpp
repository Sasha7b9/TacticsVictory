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

}

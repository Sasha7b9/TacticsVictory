// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "MenuEvents.h"
#include "MenuAboutMe.h"
#include "GUI/Controls/Button.h"
#include "GUI/Menu/MenuStart.h"



MenuAboutMe::MenuAboutMe(Context *context) : WindowMenu(context)
{
    const int width = 216;
    const int height = 130;
    const int widthButton = 100;
    const int heightButton = 20;

    SetSize(width, height);

    AddLabel("Alexandr Shevchenko", false, 20, 20, 200, 40);
    AddLabel("e-mail Sasha7b9@tut.by", false, 20, 50, 200, 40);

    int x = width / 2 - widthButton / 2;
    int y = height - 2 * heightButton;

    buttonOk = AddButton("Ok", x, y, widthButton, heightButton);

    buttons.Push(buttonOk);

    SubscribeToEvent(buttonOk, E_RELEASED, URHO3D_HANDLER(MenuAboutMe, HandleButtonRelease));

    SetMovable(false);
}


void MenuAboutMe::HandleButtonRelease(StringHash, VariantMap&)
{
    SendEventClose();
}

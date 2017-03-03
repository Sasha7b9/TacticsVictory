#include <stdafx.h>
#include "MenuEvents.h"
#include "MenuAboutMe.h"
#include "GUI/Controls/Button.h"
#include "GUI/Menu/MenuStart.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(MenuAboutMe, HandleKeyDown));

    SetMovable(false);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MenuAboutMe::HandleButtonRelease(StringHash, VariantMap&)
{
    SendEventReturn();
    SetDisabled();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MenuAboutMe::HandleKeyDown(StringHash hash, VariantMap& eventData)
{
    using namespace KeyDown;

    int key = eventData[P_KEY].GetInt();

    if (key == KEY_ESCAPE)
    {
        SendEventReturn();
        SetDisabled();
    }
    else
    {
        WindowRTS::HandleKeyDown(hash, eventData);
    }
}

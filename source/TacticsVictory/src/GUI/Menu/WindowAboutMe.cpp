#include <stdafx.h>
#include "WindowAboutMe.h"
#include "GUI/Elements/Button.h"
#include "GUI/Menu/StartMenu.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WindowAboutMe::WindowAboutMe(Context *context) : WindowRTS(context)
{
    const int width = 240;
    const int height = 130;
    const int widthButton = 100;
    const int heightButton = 20;

    SetSize(width, height);
    //SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6));

    AddLabel("Alexandr Shevchenko", false, 20, 20, 200, 40);
    AddLabel("e-mail : Sasha7b9@tut.by", false, 20, 50, 200, 40);

    int x = width / 2 - widthButton / 2;
    int y = height - 2 * heightButton;

    buttonOk = AddButton("Ok", x, y, widthButton, heightButton);

    buttons.Push(buttonOk);

    SubscribeToEvent(buttonOk, E_RELEASED, URHO3D_HANDLER(WindowAboutMe, HandleButtonRelease));
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(WindowAboutMe, HandleKeyDown));

    SetMovable(false);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowAboutMe::HandleButtonRelease(StringHash, VariantMap&)
{
    SetDisabled();
    gStartMenu->SetEnabled();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowAboutMe::HandleKeyDown(StringHash hash, VariantMap& eventData)
{
    using namespace KeyDown;

    int key = eventData[P_KEY].GetInt();

    if (key == KEY_ESCAPE)
    {
        SetDisabled();
        gStartMenu->SetEnabled();
    }
    else
    {
        WindowRTS::HandleKeyDown(hash, eventData);
    }
}

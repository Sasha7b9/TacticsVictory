#include <stdafx.h>
#include "GlobalFunctions.h"
#include "MenuRTS.h"
#include "MenuMain.h"
#include "MenuEvents.h"
#include "MenuOptions.h"
#include "MenuStart.h"
#include "MenuConfirmExit.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MenuRTS::MenuRTS(Context *context) : Object(context)
{
    menuStart = new MenuStart();
    SetWindowInCenterScreen(menuStart);
    menuStart->SetMovable(false);
    gUIRoot->AddChild(menuStart);

    /*
    gMenuMain = new MenuMain();
    SetWindowInCenterScreen(gMenuMain);

    gMenuOptions = new MenuOptions();
    SetWindowInCenterScreen(gMenuOptions);

    gMenuConfirmExit = new MenuConfirmExit();
    SetWindowInCenterScreen(gMenuConfirmExit);
    */
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
MenuRTS::~MenuRTS()
{
    //SAFE_DELETE(gMenuConfirmExit);
    //SAFE_DELETE(gMenuOptions);
    //SAFE_DELETE(gMenuMain);
    //SAFE_DELETE(gMenuStart);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MenuRTS::HandleMenuEvent(StringHash, VariantMap& eventData)
{
    uint action = eventData[MenuEvent::P_TYPE].GetUInt();

    if (action == MenuEvent_ExitInOS)
    {
        gEngine->Exit();
    }
    else if (action == MenuEvent_MenuOptionsOpen)
    {
        SetVisible(gMenuOptions, !gMenuOptions->IsVisible());
    }
    else if (action == MenuEvent_MenuOptionsClose)
    {
        gUIRoot->RemoveChild(gMenuOptions);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MenuRTS::SetVisible(bool visible)
{
    visible ? gMenuMain->SetEnabled() : gMenuMain->SetDisabled();
    gMenuOptions->SetVisible(visible);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MenuRTS::SetVisible(WindowRTS *menuWindow, bool visible)
{
    menuWindow->SetVisible(visible);
    if (visible)
    {
        menuWindow->BringToFront();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool MenuRTS::IsVisible()
{
    return true;
}

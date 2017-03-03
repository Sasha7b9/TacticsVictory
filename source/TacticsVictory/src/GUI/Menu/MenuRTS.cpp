#include <stdafx.h>
#include "GlobalFunctions.h"
#include "MenuRTS.h"
#include "MenuGame.h"
#include "MenuEvents.h"
#include "MenuOptions.h"
#include "MenuStart.h"
#include "MenuConfirmExit.h"
#include "MenuAboutMe.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CREATE_MENU(name, type, moving)                                 \
    name = new type();                                                  \
    allMenus.Push(name);                                                \
    SetWindowInCenterScreen(name);                                      \
    name->SetMovable(moving);                                           \
    SubscribeToEvent(E_MENU, URHO3D_HANDLER(MenuRTS, HandleMenuEvent));


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MenuRTS::MenuRTS(Context *context) : Object(context)
{   
    CREATE_MENU(menuStart, MenuStart, false);
//    CREATE_MENU(menuAbout, MenuAboutMe, false);

    Open(menuStart);

    /*
    gMenuMain = new MenuGame();
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
    else if (action == MenuEvent_Return)
    {

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
void MenuRTS::Open(WindowMenu* windowMenu)
{
    CloseAll();
    lifoMenus.Push(windowMenu);
    windowMenu->Open();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MenuRTS::CloseAll()
{
    for (WindowMenu *window : allMenus)
    {
        gUIRoot->RemoveChild(window);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool MenuRTS::IsActive()
{
    for (WindowMenu *window : allMenus)
    {
        if (window->GetParent())
        {
            return true;
        }
    }
    return false;
}

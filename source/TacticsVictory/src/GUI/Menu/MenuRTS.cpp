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
#define CREATE_MENU(name, type, prev, moving)                           \
    name = new type(gContext, prev);                                    \
    allMenus.Push(name);                                                \
    SetWindowInCenterScreen(name);                                      \
    name->SetMovable(moving);                                           \
    SubscribeToEvent(E_MENU, URHO3D_HANDLER(MenuRTS, HandleMenuEvent));


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MenuRTS::MenuRTS(Context *context) : Object(context)
{   
    CREATE_MENU(menuStart, MenuStart, nullptr, false);
    CREATE_MENU(menuAbout, MenuAboutMe, menuStart, false);

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
    using namespace MenuEvent;

    uint action = eventData[P_TYPE].GetUInt();

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
    else if (action == MenuEvent_Close)
    {
        WindowMenu *closed = (WindowMenu*)eventData[P_SOURCE].GetPtr();
        WindowMenu *opened = (WindowMenu*)eventData[P_DESTINATION].GetPtr();
        closed->Close();
        opened->Open();
    }
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
void MenuRTS::Open(WindowMenu* menu)
{
    CloseAll();
    lifoMenus.Push(menu);
    menu->Open();
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
    return ActiveMenu() != nullptr;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool MenuRTS::ProcessingKey(int key)
{
    WindowMenu *active = ActiveMenu();

    if(active)
    {
        if(key == KEY_ESCAPE && active == menuStart)    // Если находимся в стартовом менюю и нажата кнопка ESCAPE - ничего делать не будем
        {

        }
        else
        {
            active->ProcessingKey(key);
        }
    }

    return active != nullptr;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
WindowMenu* MenuRTS::ActiveMenu()
{
    for(WindowMenu *window : allMenus)
    {
        if(window->GetParent())
        {
            return window;
        }
    }

    return nullptr;
}

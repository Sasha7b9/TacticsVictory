// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Menu/MenuAboutMe.h"
#include "GUI/Menu/MenuEvents.h"
#include "GUI/Menu/MenuOptions.h"
#include "GUI/Menu/Menu.h"
#include "GUI/Menu/MenuStart.h"
#include "Utils/GlobalFunctions.h"


#define CREATE_MENU(name, type, moving)                                 \
    name = new type();                                                  \
    allMenus.Push(name);                                                \
    GF::SetWindowInCenterScreen(name);                                  \
    name->SetMovable(moving);                                           \
    SubscribeToEvent(E_MENU, URHO3D_HANDLER(MenuT, HandleMenuEvent));


MenuT::MenuT(Context *context) : Object(context)
{   
    CREATE_MENU(menuStart, MenuStart, false);
    CREATE_MENU(menuAbout, MenuAboutMe, false);
    CREATE_MENU(menuOptions, MenuOptions, false);

    Open(menuStart);

    /*
    TheMenuMain = new MenuGame();
    SetWindowInCenterScreen(TheMenuMain);

    gMenuOptions = new MenuOptions();
    SetWindowInCenterScreen(gMenuOptions);

    TheMenuConfirmExit = new MenuConfirmExit();
    SetWindowInCenterScreen(TheMenuConfirmExit);
    */
}


MenuT::~MenuT()
{
}


void MenuT::HandleMenuEvent(StringHash, VariantMap& eventData)
{
    using namespace MenuEvent;

    uint action = eventData[P_TYPE].GetUInt();
    WindowMenu *source = dynamic_cast<WindowMenu*>(eventData[P_SOURCE].GetPtr());
    WindowMenu *destination = dynamic_cast<WindowMenu*>(eventData[P_DESTINATION].GetPtr());

    if(action == ME_StartServer || action == ME_StartClient)
    {
        Hide();
    }
    else if (action == ME_ExitInOS)
    {
        TheEngine->Exit();
    }
    else if (action == ME_OpenOptions)
    {
        Open(menuOptions, source);
    }
    else if(action == ME_OpenAboutMe)
    {
        Open(menuAbout, source);
    }
    else if (action == ME_Close)
    {
        CALL_MEMBER_IF_EXIST(source, Close);
        CALL_MEMBER_IF_EXIST(destination, Open);
    }
}


void MenuT::Open(WindowMenu* menu, WindowMenu *prev)
{
    CloseAll();
    menu->Open(prev);
}


void MenuT::CloseAll()
{
    for (WindowMenu *window : allMenus)
    {
        TheUIRoot->RemoveChild(window);
    }
}


void MenuT::Hide()
{
    CloseAll();
}


bool MenuT::IsActive()
{
    return ActiveMenu() != nullptr;
}


bool MenuT::ProcessingKey(int key)
{
    WindowMenu *active = ActiveMenu();

    if(active)
    {
        if(KEY_IS_ESC && active == menuStart)    // Если находимся в стартовом менюю и нажата кнопка ESCAPE - ничего делать не будем
        {

        }
        else
        {
            active->ProcessingKey(key);
        }
    }

    return active != nullptr;
}


WindowMenu* MenuT::ActiveMenu()
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

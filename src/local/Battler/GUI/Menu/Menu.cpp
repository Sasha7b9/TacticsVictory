// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Menu/MenuEvents.h"
#include "GUI/Menu/Menu.h"
#include "GUI/Menu/MenuStart/MenuAboutMe.h"
#include "GUI/Menu/MenuStart/MenuOptions.h"
#include "GUI/Menu/MenuStart/MenuStart.h"
#include "GUI/Menu/MenuStart/MenuPlay/MenuFindServer.h"
#include "GUI/Menu/MenuStart/MenuPlay/MenuPlay.h"
#include "Utils/GlobalFunctions.h"


#define CREATE_MENU(name, type, moving)                                 \
    name = new type();                                                  \
    allMenus.Push(name);                                                \
    GF::SetWindowInCenterScreen(name);                                  \
    name->SetMovable(moving);                                           \
    SubscribeToEvent(E_MENU, URHO3D_HANDLER(MenuT, HandleMenuEvent));


MenuT::MenuT(MenuT **self) : Object(TheContext)
{
//    menuStart = new MenuStart();
//    allMenus.Push(menuStart);
//    GF::SetWindowInCenterScreen(menuStart);
//    menuStart->SetMovable(false);
//    SubscribeToEvent(E_MENU, URHO3D_HANDLER(MenuT, HandleMenuEvent));

    CREATE_MENU(menuStart, MenuStart, false);
    CREATE_MENU(menuAbout, MenuAboutMe, false);
    CREATE_MENU(menuOptions, MenuOptions, false);
    CREATE_MENU(menuPlay, MenuPlay, false);
    CREATE_MENU(menuFindServer, MenuFindServer, false);

    Open(menuStart, nullptr);

    *self = this;

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

    switch (action)
    {
    case ME_START_SERVER:
    case ME_START_CLIENT:       Hide();
        break;

    case ME_EXIT_IN_OS:         TheEngine->Exit();
        break;

    case ME_OPEN_ABOUT_ME:      Open(menuAbout, source);
        break;

    case ME_OPEN_FIND_SERVER:   Open(menuFindServer, source);
        break;

    case ME_OPEN_OPTIONS:       Open(menuOptions, source);
        break;

    case ME_OPEN_PLAY:          Open(menuPlay, source);
        break;

    case ME_CLOSE:              CALL_MEMBER_IF_EXIST(source, Close);
                                CALL_MEMBER_IF_EXIST(destination, Open);
        break;
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

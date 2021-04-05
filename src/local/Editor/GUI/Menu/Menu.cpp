// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Menu/MenuEvents_.h"
#include "GUI/Menu/Menu.h"
#include "GUI/Menu/MenuMain.h"
#include "GUI/Menu/MenuPlay.h"


PODVector<WindowMenu *>   allMenus;       // Здесь список всех меню
SharedPtr<MenuMain>       menuStart;
SharedPtr<MenuPlay>       menuPlay;



#define CREATE_MENU(name, type, moving)                                 \
    name = new type();                                                  \
    allMenus.Push(name);                                                \
    GF::SetWindowInCenterScreen(name);                                  \
    name->SetMovable(moving);

// SubscribeToEvent(E_MENU, URHO3D_HANDLER(::Menu, HandleMenuEvent));


void ::Menu::Create()
{
    CREATE_MENU(menuStart, MenuMain, false);
    CREATE_MENU(menuPlay, MenuPlay, false);

    Open(menuStart, nullptr);
}


void ::Menu::HandleMenuEvent(StringHash, VariantMap& eventData)
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

    case ME_OPEN_PLAY:          Open(menuPlay, source);
        break;

    case ME_CLOSE:              CALL_MEMBER_IF_EXIST(source, Close);
                                CALL_MEMBER_IF_EXIST(destination, Open);
        break;
    }
}


void ::Menu::Open(WindowMenu* menu, WindowMenu *prev)
{
    CloseAll();
    menu->Open(prev);
}


void ::Menu::CloseAll()
{
    for (WindowMenu *window : allMenus)
    {
        TheUIRoot->RemoveChild(window);
    }
}


void ::Menu::Hide()
{
    CloseAll();
}


bool ::Menu::IsActive()
{
    return ActiveMenu() != nullptr;
}


bool ::Menu::ProcessingKey(int key)
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


WindowMenu* ::Menu::ActiveMenu()
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

// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Menu/MenuEvents_.h"
#include "GUI/Menu/Menu.h"
#include "GUI/Menu/PageStart.h"


#define CREATE_PAGE(name, type, moving)                                 \
    name = new type();                                                  \
    allMenus.Push(name);                                                \
    GF::SetWindowInCenterScreen(name);                                  \
    name->SetMovable(moving);                                           \
    SubscribeToEvent(E_MENU, URHO3D_HANDLER(Menus, HandleMenuEvent));


Menus::Menus(Menus **self) : Object(TheContext)
{
    CREATE_PAGE(pageStart, PageStart, false);

    Open(pageStart, nullptr);

    *self = this;
}


void Menus::HandleMenuEvent(StringHash, VariantMap& eventData)
{
    using namespace MenuEvent;

    uint action = eventData[P_TYPE].GetUInt();
    MenuPage *source = dynamic_cast<MenuPage*>(eventData[P_SOURCE].GetPtr());
    MenuPage *destination = dynamic_cast<MenuPage*>(eventData[P_DESTINATION].GetPtr());

    switch (action)
    {
    case ME_START_SERVER:
    case ME_START_CLIENT:       Hide();
        break;

    case ME_EXIT_IN_OS:         TheEngine->Exit();
        break;

    case ME_CLOSE:              CALL_MEMBER_IF_EXIST(source, Close);
                                CALL_MEMBER_IF_EXIST(destination, Open);
        break;
    }
}


void Menus::Open(MenuPage* menu, MenuPage *prev)
{
    CloseAll();
    menu->Open(prev);
}


void Menus::CloseAll()
{
    for (MenuPage *window : allMenus)
    {
        TheUIRoot->RemoveChild(window);
    }
}


void Menus::Hide()
{
    CloseAll();
}


bool Menus::IsActive()
{
    return ActiveMenu() != nullptr;
}


bool Menus::ProcessingKey(int key)
{
    MenuPage *active = ActiveMenu();

    if(active)
    {
        if(KEY_IS_ESC && active == pageStart)    // Если находимся в стартовом менюю и нажата кнопка ESCAPE - ничего делать не будем
        {

        }
        else
        {
            active->ProcessingKey(key);
        }
    }

    return active != nullptr;
}


MenuPage* Menus::ActiveMenu()
{
    for(MenuPage *window : allMenus)
    {
        if(window->GetParent())
        {
            return window;
        }
    }

    return nullptr;
}

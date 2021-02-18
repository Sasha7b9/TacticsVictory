// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Menu/TMenuAboutMe.h"
#include "GUI/Menu/TMenuEvents.h"


#define CREATE_MENU(name, type, moving)                                 \
    name = new type();                                                  \
    allMenus.Push(name);                                                \
    GF::SetWindowInCenterScreen(name);                                  \
    name->SetMovable(moving);                                           \
    SubscribeToEvent(E_MENU, URHO3D_HANDLER(TMenu, HandleMenuEvent));


TMenu::TMenu(Context *context) : Object(context)
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


TMenu::~TMenu()
{
}


void TMenu::HandleMenuEvent(StringHash, VariantMap& eventData)
{
    using namespace MenuEvent;

    uint action = eventData[P_TYPE].GetUInt();
    WindowMenu *source = dynamic_cast<WindowMenu*>(eventData[P_SOURCE].GetPtr());
    WindowMenu *destination = dynamic_cast<WindowMenu*>(eventData[P_DESTINATION].GetPtr());

    if(action == MenuEvent_StartServer || action == MenuEvent_StartClient)
    {
        Hide();
    }
    else if (action == MenuEvent_ExitInOS)
    {
        TheEngine->Exit();
    }
    else if (action == MenuEvent_OpenOptions)
    {
        Open(menuOptions, source);
    }
    else if(action == MenuEvent_OpenAboutMe)
    {
        Open(menuAbout, source);
    }
    else if (action == MenuEvent_Close)
    {
        CALL_MEMBER_IF_EXIST(source, Close);
        CALL_MEMBER_IF_EXIST(destination, Open);
    }
}


void TMenu::Open(WindowMenu* menu, WindowMenu *prev)
{
    CloseAll();
    menu->Open(prev);
}


void TMenu::CloseAll()
{
    for (WindowMenu *window : allMenus)
    {
        TheUIRoot->RemoveChild(window);
    }
}


void TMenu::Hide()
{
    CloseAll();
}


bool TMenu::IsActive()
{
    return ActiveMenu() != nullptr;
}


bool TMenu::ProcessingKey(int key)
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


WindowMenu* TMenu::ActiveMenu()
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

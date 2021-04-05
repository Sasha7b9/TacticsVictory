// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class MenuAboutMe;
class MenuFindServer;
class MenuOptions;
class MenuPlay;
class MenuMain;
class WindowMenu;


class Menu : public Object
{
    URHO3D_OBJECT(Menu, Object)

public:
    Menu(Menu **self);
    ~Menu();
    void Hide();
    bool IsActive();
    bool ProcessingKey(int key);

private:
    PODVector<WindowMenu*>    allMenus;       // Здесь список всех меню
    SharedPtr<MenuMain>      menuStart;
    SharedPtr<MenuAboutMe>    menuAbout;
    SharedPtr<MenuPlay>       menuPlay;
    SharedPtr<MenuFindServer> menuFindServer;

    WindowMenu* ActiveMenu();
    void Open(WindowMenu* menu, WindowMenu *prev);    // Открыть меню menu, при этом его хранителем указать prev
    void CloseAll();
    void HandleMenuEvent(StringHash, VariantMap&);
};


/*
           +-----------+
           | MenuStart |
           +-----------+



*/

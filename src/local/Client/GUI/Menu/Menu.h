// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class PageAboutMe;
class PageFindServer;
class MenuOptions;
class PagePlay;
class PageMain;
class MenuPage;


class Menus : public Object
{
    URHO3D_OBJECT(Menus, Object);

public:

    Menus(Menus **self);

    void Hide();
    bool IsActive();
    bool ProcessingKey(int key);

private:
    PODVector<MenuPage *>     allMenus;    // Здесь список всех меню
    SharedPtr<PageMain>       menuStart;
    SharedPtr<PageAboutMe>    menuAbout;
    SharedPtr<PagePlay>       menuPlay;
    SharedPtr<PageFindServer> menuFindServer;

    MenuPage* ActiveMenu();

    void Open(MenuPage* menu, MenuPage *prev);    // Открыть меню menu, при этом его хранителем указать prev
    void CloseAll();
    void HandleMenuEvent(StringHash, VariantMap&);
};

// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class PageAboutMe;
class PageFindServer;
class PageOptions;
class PagePlay;
class PageStart;
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
    SharedPtr<PageStart>      pageStart;
    SharedPtr<PageAboutMe>    pageAbout;
    SharedPtr<PagePlay>       pagePlay;
    SharedPtr<PageFindServer> pageFindServer;
    SharedPtr<PageOptions>    pageOptions;

    MenuPage* ActiveMenu();

    void Open(MenuPage* page, MenuPage *prev);    // Открыть меню menu, при этом его хранителем указать prev
    void CloseAll();
    void HandleMenuEvent(StringHash, VariantMap&);
};

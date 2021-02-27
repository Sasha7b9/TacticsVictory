// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class WindowMenu;
class MenuAboutMe;
class MenuOptions;
class MenuStart;


class TMenu : public Object
{
    URHO3D_OBJECT(TMenu, Object)

public:
    TMenu(Context *context = TheContext);
    ~TMenu();
    void Hide();
    bool IsActive();
    bool ProcessingKey(int key);

private:
    PODVector<WindowMenu*>  allMenus;                           // Здесь список всех меню
    SharedPtr<MenuStart>    menuStart;
    SharedPtr<MenuAboutMe>  menuAbout;
    SharedPtr<MenuOptions>  menuOptions;

    WindowMenu* ActiveMenu();
    void Open(WindowMenu* menu, WindowMenu *prev = nullptr);    // Открыть меню menu, при этом его хранителем указать prev
    void CloseAll();
    void HandleMenuEvent(StringHash, VariantMap&);
};

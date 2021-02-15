#pragma once



class WindowMenu;
class MenuAboutMe;



class MenuRTS : public Object
{
    URHO3D_OBJECT(MenuRTS, Object)

public:
    MenuRTS(Context *context = gContext);
    ~MenuRTS();
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

    DEFAULT_MEMBERS(MenuRTS);
};

#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WindowMenu;
class MenuAboutMe;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MenuRTS : public Object
{
    friend class MenuStart;

    URHO3D_OBJECT(MenuRTS, Object)

public:
    MenuRTS(Context *context = gContext);
    ~MenuRTS();
    bool IsActive();
    void SetVisible(WindowRTS *menuWindow, bool visible);
    bool ProcessingKey(int key);

private:
    PODVector<WindowMenu*>  lifoMenus;      // Очередь открытых меню
    PODVector<WindowMenu*>  allMenus;       // Здесь список всех меню
    SharedPtr<MenuStart>    menuStart;
    SharedPtr<MenuAboutMe>  menuAbout;

    WindowMenu* ActiveMenu();
    void Open(WindowMenu* menu);
    void CloseAll();
    void HandleMenuEvent(StringHash, VariantMap&);
};

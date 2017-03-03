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
    void SetVisible(bool visible);
    void SetVisible(WindowRTS *menuWindow, bool visible);

private:
    PODVector<WindowMenu*>  lifoMenus;      // Очередь открытых меню
    PODVector<WindowMenu*>  allMenus;       // Здесь список всех меню
    SharedPtr<MenuStart>    menuStart;
    SharedPtr<MenuAboutMe>  menuAbout;

    void Open(WindowMenu* windowMenu);
    void CloseAll();
    void HandleMenuEvent(StringHash, VariantMap&);
};

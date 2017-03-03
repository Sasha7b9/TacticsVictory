#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WindowMenu;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MenuRTS : public Object
{
    URHO3D_OBJECT(MenuRTS, Object)
public:
    MenuRTS(Context *context = gContext);
    ~MenuRTS();
    void SetVisible(bool visible);
    void SetVisible(WindowRTS *menuWindow, bool visible);
    bool IsVisible();

private:
    PODVector<WindowMenu*> lifoMenus;               // Очередь открытых меню
    SharedPtr<MenuStart> menuStart;

    void HandleMenuEvent(StringHash, VariantMap&);
};

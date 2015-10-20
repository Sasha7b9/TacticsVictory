#pragma once


EVENT(E_MENU, MenuEvent)
{
    PARAM(P_TYPE, MenuEventType);
}


enum
{
    MenuEvent_MenuOptionsOpen = 0,
    MenuEvent_NewGame = 1,
    MenuEvent_OpenEditor = 3,
    MenuEvent_ExitInOS = 4
};


class vWindow;


class vGUI : public Object
{
    OBJECT(vGUI);

public:
    vGUI();
    ~vGUI();

    void Create();
    bool GheckOnDeadZoneForCursorBottomScreen(int x);
    bool MenuIsVisible();
    void SetVisibleMenu(bool visible);
    void SetVisibleMenu(vWindow *menuWindow, bool visible);

private:
    vGUI& operator=(const vGUI&)
    {};
    void HandleGuiEvent(StringHash eventType, VariantMap& eventData);
};

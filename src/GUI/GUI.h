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


class lWindow;


class lGUI : public Object
{
    OBJECT(lGUI);

public:
    lGUI();
    ~lGUI();

    void Create();
    bool GheckOnDeadZoneForCursorBottomScreen(int x);
    bool MenuIsVisible();
    void SetVisibleMenu(bool visible);
    void SetVisibleMenu(lWindow *menuWindow, bool visible);

private:
    lGUI& operator=(const lGUI&)
    {};
    void HandleGuiEvent(StringHash eventType, VariantMap& eventData);
};

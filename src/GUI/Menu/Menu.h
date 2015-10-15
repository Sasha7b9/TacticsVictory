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


class tvMenu : public UIElement
{
    OBJECT(tvMenu);

public:
    tvMenu(Context *context);

    static void RegisterObject(Context* context);

    void Log();

private:
    tvMenu& operator=(const tvMenu&) {};

    void HandleMenuEvent(StringHash eventType, VariantMap& eventData);

    Text *text = nullptr;
    SharedPtr<tvMenuMain>     menuMain;
    SharedPtr<tvMenuOptions>  menuOptions;
    //bool hidden = false;
};
#pragma once


class lMenuGame : public UIElement
{
    OBJECT(lMenuGame)

public:
    lMenuGame(Context* context);

    static void RegisterObject(Context* context);
    bool CheckOnDeadZoneForCursorBottomScreen(int x);

private:
    lMenuGame& operator=(const lMenuGame&)
    {};

    SharedPtr<lButton> buttonMap;
    SharedPtr<lButton> buttonMainPanel;
    SharedPtr<lButton> buttonMenu;

    SharedPtr<lPanelBottom> panelBottom;
    SharedPtr<lPanelMap>    panelMap;
    SharedPtr<lPanelMain>   panelMain;

    void HandleButtonRelease(StringHash, VariantMap &eventData);

    bool IntersectionX(lButton *button, int x);
};
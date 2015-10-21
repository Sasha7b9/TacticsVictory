#pragma once


class lGuiGame : public UIElement
{
    OBJECT(lGuiGame)

public:
    lGuiGame(Context* context);

    static void RegisterObject(Context* context);
    bool CheckOnDeadZoneForCursorBottomScreen(int x);
    bool IsInside(IntVector2 &position);

private:
    lGuiGame& operator=(const lGuiGame&)
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
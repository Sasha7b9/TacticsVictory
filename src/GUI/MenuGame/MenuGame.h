#pragma once


class tvMenuGame : public UIElement
{
    OBJECT(tvMenuGame)

public:
    tvMenuGame(Context* context);

    static void RegisterObject(Context* context);
    bool CheckOnDeadZoneForCursorBottomScreen(int x);

private:
    tvMenuGame& operator=(const tvMenuGame&)
    {};

    SharedPtr<tvButton> buttonMap;
    SharedPtr<tvButton> buttonMainPanel;
    SharedPtr<tvButton> buttonMenu;

    SharedPtr<tvPanelBottom> panelBottom;
    SharedPtr<tvPanelMap>    panelMap;
    SharedPtr<tvPanelMain>   panelMain;

    void HandleButtonRelease(StringHash, VariantMap &eventData);

    bool IntersectionX(tvButton *button, int x);
};
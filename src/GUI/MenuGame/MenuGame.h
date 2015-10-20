#pragma once


class vMenuGame : public UIElement
{
    OBJECT(vMenuGame)

public:
    vMenuGame(Context* context);

    static void RegisterObject(Context* context);
    bool CheckOnDeadZoneForCursorBottomScreen(int x);

private:
    vMenuGame& operator=(const vMenuGame&)
    {};

    SharedPtr<vButton> buttonMap;
    SharedPtr<vButton> buttonMainPanel;
    SharedPtr<vButton> buttonMenu;

    SharedPtr<vPanelBottom> panelBottom;
    SharedPtr<vPanelMap>    panelMap;
    SharedPtr<vPanelMain>   panelMain;

    void HandleButtonRelease(StringHash, VariantMap &eventData);

    bool IntersectionX(vButton *button, int x);
};
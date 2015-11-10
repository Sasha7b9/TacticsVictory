#pragma once


class GuiGame : public UIElement
{
    URHO3D_OBJECT(GuiGame, UIElement);

public:
    GuiGame(Context* context);

    static void RegisterObject(Context* context);
    bool CheckOnDeadZoneForCursorBottomScreen(int x);
    bool IsInside(IntVector2 &position);

private:
    GuiGame& operator=(const GuiGame&)
    {};

    SharedPtr<ButtonMain> buttonMap;
    SharedPtr<ButtonMain> buttonMainPanel;
    SharedPtr<ButtonMain> buttonMenu;

    SharedPtr<PanelBottom> panelBottom;
    SharedPtr<PanelMap>    panelMap;
    SharedPtr<PanelMain>   panelMain;

    void HandleButtonRelease(StringHash, VariantMap &eventData);

    bool IntersectionX(ButtonMain *button, int x);
};
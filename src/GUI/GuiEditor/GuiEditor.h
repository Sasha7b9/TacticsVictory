#pragma once


class lGuiEditor : public UIElement
{
    OBJECT(lGuiEditor)

public:
    lGuiEditor(Context* context);

    static void RegisterObject(Context *context);
    bool CheckOnDeadZoneForCursorBottomScreen(int x);
    bool IsInside(IntVector2 &position);
    void TogglePanelMain();
    void TogglePanelMap();

private:
    lGuiEditor& operator=(const lGuiEditor&) {};

    SharedPtr<lButton> buttonMap;
    SharedPtr<lButton> buttonMainPanel;
    SharedPtr<lButton> buttonMenu;

    SharedPtr<lButtonToggled> buttonMainFile;

    SharedPtr<lPanelBottom> panelBottom;
    SharedPtr<lPanelMap>    panelMap;
    SharedPtr<lPanelMain>   panelMain;

    void HandleButtonRelease(StringHash eventType, VariantMap &eventData);

    bool IntersectionX(lButton *button, int x);
};
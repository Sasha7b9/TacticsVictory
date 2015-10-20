#pragma once


class lMenuEditor : public UIElement
{
    OBJECT(lMenuEditor)

public:
    lMenuEditor(Context* context);

    static void RegisterObject(Context *context);
    bool CheckOnDeadZoneForCursorBottomScreen(int x);

private:
    lMenuEditor& operator=(const lMenuEditor&) {};

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
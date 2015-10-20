#pragma once


class vMenuEditor : public UIElement
{
    OBJECT(vMenuEditor)

public:
    vMenuEditor(Context* context);

    static void RegisterObject(Context *context);
    bool CheckOnDeadZoneForCursorBottomScreen(int x);

private:
    vMenuEditor& operator=(const vMenuEditor&) {};

    SharedPtr<vButton> buttonMap;
    SharedPtr<vButton> buttonMainPanel;
    SharedPtr<vButton> buttonMenu;

    SharedPtr<vButtonToggled> buttonMainFile;

    SharedPtr<vPanelBottom> panelBottom;
    SharedPtr<vPanelMap>    panelMap;
    SharedPtr<vPanelMain>   panelMain;

    void HandleButtonRelease(StringHash eventType, VariantMap &eventData);

    bool IntersectionX(vButton *button, int x);
};
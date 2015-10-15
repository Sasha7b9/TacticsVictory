#pragma once


class tvMenuEditor : public UIElement
{
    OBJECT(tvMenuEditor)

public:
    tvMenuEditor(Context* context);

    static void RegisterObject(Context *context);
    bool CheckOnDeadZoneForCursorBottomScreen(int x);

private:
    tvMenuEditor& operator=(const tvMenuEditor&) {};

    SharedPtr<tvButton> buttonMap;
    SharedPtr<tvButton> buttonMainPanel;
    SharedPtr<tvButton> buttonMenu;

    SharedPtr<tvButtonToggled> buttonMainFile;

    SharedPtr<tvPanelBottom> panelBottom;
    SharedPtr<tvPanelMap>    panelMap;
    SharedPtr<tvPanelMain>   panelMain;

    void HandleButtonRelease(StringHash eventType, VariantMap &eventData);

    bool IntersectionX(tvButton *button, int x);
};
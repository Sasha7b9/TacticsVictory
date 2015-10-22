#pragma once


class lWindow;

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

    SharedPtr<lButton> btnNewMap;

    SharedPtr<lPanelBottom> panelBottom;
    SharedPtr<lPanelMap>    panelMap;
    SharedPtr<lPanelMain>   panelMain;

    SharedPtr<lWindow>      windowNewMap;

    void HandleButtonRelease(StringHash, VariantMap&);
    void HandleCreateNewMap(StringHash, VariantMap&);
    void HandleClearTerrain(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);
    void HandleOpenMapFromFile(StringHash, VariantMap&);
    void HandleSaveMapToFile(StringHash, VariantMap&);

    bool IntersectionX(lButton *button, int x);
    void CreateWindows();
};
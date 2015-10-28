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

    enum ModeSelect
    {
        ModeSelect_Plane,
        ModeSelect_Edge
    } modeSelect = ModeSelect_Plane;

private:
    lGuiEditor& operator=(const lGuiEditor&) {};

    SharedPtr<lButton> buttonInterface;
    SharedPtr<lButton> buttonMenu;

    SharedPtr<lButton> btnNewMap;

    SharedPtr<lPanelBottom> panelBottom;
    SharedPtr<lPanelMap>    panelMap;
    SharedPtr<lPanelMain>   panelMain;

    SharedPtr<lWindow>      windowNewMap;
    SharedPtr<lWindow>      windowMenu;
    SharedPtr<lWindow>      windowConfirmExit;
    SharedPtr<lSliderWithTextAndButtons> sliderSizeNewMapX;
    SharedPtr<lSliderWithTextAndButtons> sliderSizeNewMapY;

    void HandleMouseDown(StringHash, VariantMap&);
    void HandleButtonRelease(StringHash, VariantMap&);
    void HandleExit(StringHash, VariantMap&);
    void HandleOptions(StringHash, VariantMap&);
    void HandleExitOk(StringHash, VariantMap&);
    void HandleExitCancel(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);

    // Tab "File"
    void HandleFileLoad(StringHash, VariantMap&);
    void HandleFileSave(StringHash, VariantMap&);
    void HandleFileSelectorLoadLandscape(StringHash, VariantMap&);
    void HandleFileSelectorSaveLandscape(StringHash, VariantMap&);

    // Tab "Edit"
    void HandleEditUndo(StringHash, VariantMap&);
    void HandleEditRedo(StringHash, VariantMap&);

    // Tab "Landscape"
    void HandleLandscapeCreateNewMap(StringHash, VariantMap&);
    void HandleLandscapeClearTerrain(StringHash, VariantMap&);
    void HandleLandscapeModeSelectChanged(StringHash, VariantMap&);

    // Tab "Objects"
    void HandleObjectsAdd(StringHash, VariantMap&);

    bool IntersectionX(lButton *button, int x);
    void CreateWindows();
    void ToggleInterfacePanels();
};
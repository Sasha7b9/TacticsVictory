#pragma once


class lWindow;

class GuiEditor : public UIElement
{
    OBJECT(GuiEditor)

public:
    GuiEditor(UContext* context = gContext);

    static void RegisterObject(UContext *context = gContext);

    bool CheckOnDeadZoneForCursorBottomScreen(int x);
    bool IsInside(IntVector2 &position);

    enum ModeSelect
    {
        ModeSelect_Plane,
        ModeSelect_Edge
    } modeSelect = ModeSelect_Plane;

private:
    GuiEditor& operator=(const GuiEditor&) {};

    SharedPtr<ButtonMain> buttonInterface;
    SharedPtr<ButtonMain> buttonMenu;

    SharedPtr<ButtonMain> btnNewMap;

    SharedPtr<PanelBottom> panelBottom;
    SharedPtr<PanelMap>    panelMap;
    SharedPtr<PanelMain>   panelMain;

    SharedPtr<lWindow>      windowNewMap;
    SharedPtr<lWindow>      windowMenu;
    SharedPtr<lWindow>      windowConfirmExit;
    SharedPtr<SliderWithTextAndButtons> sliderSizeNewMapX;
    SharedPtr<SliderWithTextAndButtons> sliderSizeNewMapY;

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

    bool IntersectionX(ButtonMain *button, int x);
    void CreateWindows();
    void ToggleInterfacePanels();
};
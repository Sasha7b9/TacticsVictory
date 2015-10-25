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

private:
    lGuiEditor& operator=(const lGuiEditor&) {};

    SharedPtr<lButton> buttonInterface;
    SharedPtr<lButton> buttonMenu;

    SharedPtr<lButtonToggled> buttonMainFile;

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
    void HandleCreateNewMap(StringHash, VariantMap&);
    void HandleExit(StringHash, VariantMap&);
    void HandleOptions(StringHash, VariantMap&);
    void HandleExitOk(StringHash, VariantMap&);
    void HandleExitCancel(StringHash, VariantMap&);
    void HandleClearTerrain(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);
    void HandleButtonFileLoad(StringHash, VariantMap&);
    void HandleButtonFileSave(StringHash, VariantMap&);
    void HandleFileSelectorLoadLandscape(StringHash, VariantMap&);
    void HandleFileSelectorSaveLandscape(StringHash, VariantMap&);

    bool IntersectionX(lButton *button, int x);
    void CreateWindows();
    void ToggleInterfacePanels();
};
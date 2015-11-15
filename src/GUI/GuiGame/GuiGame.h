#pragma once


class GuiGame : public UIElement
{
    URHO3D_OBJECT(GuiGame, UIElement);

public:
    GuiGame(Context* context = gContext);

    static void RegisterObject(Context* context);

    bool CheckOnDeadZoneForCursorBottomScreen(int x);
    bool IsInside(IntVector2 &position);

private:
    GuiGame& operator=(const GuiGame&)
    {};

    SharedPtr<ButtonMain> buttonInterface;
    SharedPtr<ButtonMain> buttonMenu;

    SharedPtr<PanelBottom> panelBottom;
    SharedPtr<PanelMap>    panelMap;
    SharedPtr<PanelMain>   panelMain;

    bool IntersectionX(ButtonMain *button, int x);
    void ToggleInterfacePanels();

    void CreatePanels();
    void CreateTabs();
    void CreateTabInfo();
    void CreateTabUnits();
    void CreateTabPlatoons();
    void CreateTabBuildings();
    void CreateTabDebug();

    void HandleButtonRelease(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);
};
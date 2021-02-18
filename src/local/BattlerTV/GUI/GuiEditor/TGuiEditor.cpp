// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Editor/TEditor.h"
#include "GUI/TGUI.h"


GuiEditor::GuiEditor(Context* context) : Object(context)
{
    CreatePanels();

    CreateTabs();

    CreateWindows();

    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(GuiEditor, HandleKeyDown));
}


void GuiEditor::CreatePanels()
{
    panelMap = new PanelMap();
    TheUIRoot->AddChild(panelMap);

    panelMain = new PanelMain();
    TheUIRoot->AddChild(panelMain);

    // Panel bottom
    panelBottom = new PanelBottom();
    panelBottom->SetPosition(0, TheSet->GetInt(TV_SCREEN_HEIGHT) - TheSet->GetInt(TV_PANEL_BOTTOM_HEIGHT));

    width = TheSet->GetInt(TV_PANEL_BOTTOM_BUTTON_WIDTH);
    height = TheSet->GetInt(TV_PANEL_BOTTOM_BUTTON_HEIGHT);

    x = TheSet->GetInt(TV_PANEL_MAP_WIDTH) / 2 - width / 2;
    y = TheSet->GetInt(TV_PANEL_BOTTOM_BUTTON_Y);

    buttonInterface = panelBottom->AddButton("Interface", x, y, width, height);
    SubscribeToEvent(buttonInterface, E_RELEASED, URHO3D_HANDLER(GuiEditor, HandleButtonRelease));

    x = TheSet->GetInt(TV_SCREEN_WIDTH) - 2 * width;
    buttonMenu = panelBottom->AddButton("Menu", x, y, width, height);
    SubscribeToEvent(buttonMenu, E_RELEASED, URHO3D_HANDLER(GuiEditor, HandleButtonRelease));

    TheUIRoot->AddChild(panelBottom);
    panelBottom->BringToFront();
}


void GuiEditor::CreateTabs()
{
    CreateTabFile();
    CreateTabEdit();
    CreateTabTerrain();
    CreateTabObjects();
}


void GuiEditor::CreateTabFile()
{
    SharedPtr<Tab> tabFile(Tab::Create("File"));
    panelMain->AddTab(tabFile);

    SharedPtr<ButtonTV> btnFileOpen = tabFile->AddButton("Load", 10, y, width, height);
    btnFileOpen->SetHint("loadMapFromFile");
    SubscribeToEvent(btnFileOpen, E_RELEASED, URHO3D_HANDLER(GuiEditor, HandleFileLoad));

    SharedPtr<ButtonTV> btnFileSave = tabFile->AddButton("Save", 10, y += dY, width, height);
    btnFileSave->SetHint("saveMapToFile");
    SubscribeToEvent(btnFileSave, E_RELEASED, URHO3D_HANDLER(GuiEditor, HandleFileSave));
}


void GuiEditor::CreateTabEdit()
{
    SharedPtr<Tab> tabEdit(Tab::Create("Edit"));
    panelMain->AddTab(tabEdit);

    y = 10;

    SharedPtr<ButtonTV> btnEditUndo = tabEdit->AddButton("Undo", x, y, width, height);
    btnEditUndo->SetHint("hintEditUndo");
    SubscribeToEvent(btnEditUndo, E_RELEASED, URHO3D_HANDLER(GuiEditor, HandleEditUndo));

    SharedPtr<ButtonTV>  btnEditRedo = tabEdit->AddButton("Redo", x, y += dY, width, height);
    btnEditRedo->SetHint("hintEditRedo");
    SubscribeToEvent(btnEditRedo, E_RELEASED, URHO3D_HANDLER(GuiEditor, HandleEditRedo));
}


void GuiEditor::CreateTabTerrain()
{
    SharedPtr<Tab> tabTerrain(Tab::Create("Terrain"));
    panelMain->AddTab(tabTerrain);

    btnNewMap = tabTerrain->AddButton("New map", 10, y = 10, width, height);
    btnNewMap->SetHint("createNewMap");
    SubscribeToEvent(btnNewMap, E_RELEASED, URHO3D_HANDLER(GuiEditor, HandleButtonRelease));

    SharedPtr<ButtonTV> btnClearTerrain = tabTerrain->AddButton("Clear", 10, y += dY, width, height);
    btnClearTerrain->SetHint("clearTerrain");
    SubscribeToEvent(btnClearTerrain, E_RELEASED, URHO3D_HANDLER(GuiEditor, HandleTerrainClearTerrain));

    SharedPtr<SliderWithTextAndButtons> sliderHeightDefault = tabTerrain->AddSlider("", -100, 100, 1, btnClearTerrain->GetPosition().x_ + btnClearTerrain->GetWidth() + 5, y - 2, 0, 20);
    sliderHeightDefault->SetValue(0);
    sliderHeightDefault->SetHint("hintSliderDefaultHeight");

    SharedPtr<SliderWithTextAndButtons> sliderSizeBrushX = tabTerrain->AddSlider("Brush X", 1, 10, 1, 10, y += dY, 75, 50);
    sliderSizeBrushX->SetValue(1);
    sliderSizeBrushX->SetHint("hintSliderSizeBrushX");

    SharedPtr<SliderWithTextAndButtons> sliderSizeBrushY = tabTerrain->AddSlider("Brush Y", 1, 10, 1, 10, y += dY, 75, 50);
    sliderSizeBrushY->SetValue(1);
    sliderSizeBrushY->SetHint("hintSliderSizeBrushY");

    char *items[] = {"TPlane", "Edge"};
    SharedPtr<DropDownListWithTextAndButton> ddListModeSelect = tabTerrain->AddDDList("Mode select", 100, 80, 2, items, 10, y += dY);
    SubscribeToEvent(ddListModeSelect, E_ITEMSELECTED, URHO3D_HANDLER(GuiEditor, HandleTerrainModeSelectChanged));
}


void GuiEditor::CreateTabObjects()
{
    SharedPtr<Tab> tabObjects(Tab::Create("Objects"));
    panelMain->AddTab(tabObjects);

    y = 10;

    SharedPtr<ButtonTV> btnObjectsAdd = tabObjects->AddButton("Add", x, y, width, height);
    btnObjectsAdd->SetHint("hintObjectsAdd");
    SubscribeToEvent(btnObjectsAdd, E_RELEASED, URHO3D_HANDLER(GuiEditor, HandleObjectsAdd));
}


void GuiEditor::ToggleInterfacePanels()
{
    LineTranslator2D::State stateMap = panelMap->GetTranslator()->GetState();
    LineTranslator2D::State stateMain = panelMain->GetTranslator()->GetState();

    if(stateMap == LineTranslator2D::State_PointStart && stateMain == LineTranslator2D::State_PointStart)
    {
        panelMain->Toggle();
    }
    else if(stateMap == LineTranslator2D::State_PointStart && stateMain == LineTranslator2D::State_PointFinish)
    {
        panelMap->Toggle();
    }
    else if(stateMap == LineTranslator2D::State_PointFinish && stateMain == LineTranslator2D::State_PointFinish)
    {
        panelMap->Toggle();
        panelMain->Toggle();
    }
}


void GuiEditor::HandleButtonRelease(StringHash, VariantMap &eventData)
{
    ButtonTV *button = (ButtonTV*)eventData[Released::P_ELEMENT].GetPtr();

    if (button == buttonInterface)
    {
        ToggleInterfacePanels();
    }
    else if (button == btnNewMap)
    {
        windowNewMap->SetVisible(!windowNewMap->IsVisible());
        if(windowNewMap->IsVisible())
        {
            TheOpenedWindow.Push(windowNewMap);
            windowNewMap->BringToFront();
        }
    }
    else if(button == buttonMenu)
    {
        windowMenu->SetVisible(!windowMenu->IsVisible());
        if(windowMenu->IsVisible())
        {
            TheOpenedWindow.Push(windowMenu);
            windowMenu->SetPosition(buttonMenu->GetPosition().x_, panelBottom->GetPosition().y_ - windowMenu->GetHeight());
            windowMenu->BringToFront();
        }
    }
}


bool GuiEditor::IntersectionX(const ButtonTV *button, int x_)
{
    return x_ >= button->GetPosition().x_ && x_ <= button->GetPosition().x_ + button->GetWidth();
}


bool GuiEditor::CheckOnDeadZoneForCursorBottomScreen(int x_)
{
    return IntersectionX(buttonInterface, x_) || IntersectionX(buttonMenu, x_);
}


bool GuiEditor::IsInside(const IntVector2 &position)
{
    return IsVisible() && 
        (
            panelBottom->IsInside(position, true) || 
            panelMain->IsInside(position, true) || 
            panelMap->IsInside(position, true) ||
            windowNewMap->IsInside(position, true)
        ) && 
        position.x_ > 0 && 
        position.x_ < TheSet->GetInt(TV_SCREEN_WIDTH) - 1 &&
        position.y_ < TheSet->GetInt(TV_SCREEN_HEIGHT) - 1;
}


void GuiEditor::CreateWindows()
{
    // window new map
    windowNewMap = new TWindow();
    SET_VERTICAL_LAYOUT_0_6(windowNewMap);

    windowNewMap->AddLabel("CreateNewMap");
    sliderSizeNewMapX = windowNewMap->AddSlider("Dimension X", 50, 250, 50);
    sliderSizeNewMapX->SetValue(150);
    sliderSizeNewMapY = windowNewMap->AddSlider("Dimension Y", 50, 250, 50);
    sliderSizeNewMapY->SetValue(150);
    SharedPtr<ButtonTV> buttonCreateMap = windowNewMap->AddButton("Create");
    SubscribeToEvent(buttonCreateMap, E_RELEASED, URHO3D_HANDLER(GuiEditor, HandleTerrainCreateNewMap));

    windowNewMap->SetFixedSize(windowNewMap->GetSize());
    GF::SetWindowInCenterScreen(windowNewMap);
    TheUIRoot->AddChild(windowNewMap);
    windowNewMap->SetVisible(false);

    // window menu
    windowMenu = new TWindow();
    SET_VERTICAL_LAYOUT_0_0(windowMenu);

    SharedPtr<ButtonTV> buttonOptions = windowMenu->AddButton("Options");
    SubscribeToEvent(buttonOptions, E_RELEASED, URHO3D_HANDLER(GuiEditor, HandleOptions));
    SharedPtr<ButtonTV> buttonExit = windowMenu->AddButton("Exit");
    SubscribeToEvent(buttonExit, E_RELEASED, URHO3D_HANDLER(GuiEditor, HandleExit));

    windowMenu->SetFixedWidth(buttonMenu->GetWidth());
    windowMenu->SetFixedSize(windowMenu->GetSize());
    TheUIRoot->AddChild(windowMenu);
    windowMenu->SetVisible(false);

    // window confirm exit
    windowConfirmExit = new TWindow();
    SET_VERTICAL_LAYOUT_0_6(windowConfirmExit);

    SharedPtr<Label> label(Label::Create("Exit in main menu?"));
    windowConfirmExit->AddChild(label);

    SharedPtr<UIElement> layer(windowConfirmExit->CreateChild<UIElement>());
    SET_HORIZONTAL_LAYOUT_6_6(layer);

    SharedPtr<ButtonTV> buttonOk(new ButtonTV(layer, "Ok"));
    SubscribeToEvent(buttonOk, E_RELEASED, URHO3D_HANDLER(GuiEditor, HandleExitOk));

    SharedPtr<ButtonTV> buttonCancel(new ButtonTV(layer, "Cancel"));
    SubscribeToEvent(buttonCancel, E_RELEASED, URHO3D_HANDLER(GuiEditor, HandleExitCancel));

    windowConfirmExit->AddChild(layer);

    TheUIRoot->AddChild(windowConfirmExit);
    windowConfirmExit->SetVisible(false);
    GF::SetWindowInCenterScreen(windowConfirmExit);

    SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(GuiEditor, HandleMouseDown));
}


void GuiEditor::HandleTerrainCreateNewMap(StringHash, VariantMap&)
{
    Vector<Vector<float>> map = TheLevel->CreateRandom((uint)sliderSizeNewMapY->GetValue(), (uint)sliderSizeNewMapX->GetValue());
    SAFE_DELETE(TheTerrain); //-V809
    TheTerrain = new TTerrain();
    TheTerrain->CreateFromVector(map);
    windowNewMap->SetVisible(false);

    TheCamera->SetPosition({TheLevel->GetWidth() / 2.0f, 20.0f, -(float)TheLevel->GetHeight()}, {TheLevel->GetWidth() / 2.0f, 0.0f, -(TheLevel->GetHeight() / 2.0f)});
}


void GuiEditor::HandleTerrainClearTerrain(StringHash, VariantMap&)
{
    for (uint row = 0; row < TheTerrain->NumRows(); row++)
    {
        for (uint col = 0; col < TheTerrain->NumCols(); col++)
        {
            TheTerrain->SetHeight(row, col, 0.0f);
        }
    }

    TheTerrain->Update();
}


void GuiEditor::HandleKeyDown(StringHash, VariantMap& eventData) //-V2009
{
    if (!IsVisible() || TheConsole->IsActive())
    {
        return;
    }

    int key = eventData[KeyDown::P_KEY].GetInt();

    if (TheFileSelector->GetWindow()->IsVisible())
    {
        if (KEY_IS_ESC)
        {
            UnsubscribeFromEvent(TheFileSelector, E_FILESELECTED);
            TheFileSelector->GetWindow()->SetVisible(false);
            TheCamera->SetEnabled(true);
        }
        return;
    }

    if (KEY_IS_ESC)
    {
        if(!TheOpenedWindow.Empty())
        {
            TWindow *window = TheOpenedWindow.Back();
            window->SetVisible(false);
            TheOpenedWindow.Remove(window);
        }
    }
    else if (KEY_IS_I)
    {
        ToggleInterfacePanels();
    }
}


void GuiEditor::HandleFileLoad(StringHash, VariantMap&)
{
    TheCamera->SetEnabled(false);

    Vector<String> filters;

    filters.Push("*.map");

    GF::OpenFileSelector("Load landscape", "Load", "Cancel", filters);

    SubscribeToEvent(TheFileSelector, E_FILESELECTED, URHO3D_HANDLER(GuiEditor, HandleFileSelectorLoadTerrain));
}


void GuiEditor::HandleFileSave(StringHash, VariantMap&)
{
    TheCamera->SetEnabled(false);

    Vector<String> filters;

    filters.Push("*.map");

    GF::OpenFileSelector("Save landscape", "Save", "Cancel", filters);

    SubscribeToEvent(TheFileSelector, E_FILESELECTED, URHO3D_HANDLER(GuiEditor, HandleFileSelectorSaveTerrain));
}


void GuiEditor::HandleFileSelectorLoadTerrain(StringHash, VariantMap& eventData)
{
    UnsubscribeFromEvent(TheFileSelector, E_FILESELECTED);

    bool ok = (bool)eventData[FileSelected::P_OK].GetBool();

    if(ok)
    {
        Vector<Vector<float>> map = TheLevel->Load((char*)((String)eventData[FileSelected::P_FILENAME].GetString()).CString());
        SAFE_DELETE(TheTerrain); //-V809
        TheTerrain = new TTerrain();
        TheTerrain->CreateFromVector(map);
        TheCamera->SetPosition({TheLevel->GetWidth() / 2.0f, 20.0f, -(float)TheLevel->GetHeight()}, {TheLevel->GetWidth() / 2.0f, 0.0f, -(TheLevel->GetHeight() / 2.0f)});
    }
    
    TheFileSelector->GetWindow()->SetVisible(false);

    TheCamera->SetEnabled(true);
}


void GuiEditor::HandleFileSelectorSaveTerrain(StringHash, VariantMap& eventData) //-V2009
{
    UnsubscribeFromEvent(TheFileSelector, E_FILESELECTED);

    bool ok = (bool)eventData[FileSelected::P_OK].GetBool();

    if (ok)
    {
        String fileName = (String)eventData[FileSelected::P_FILENAME].GetString();
        fileName = ReplaceExtension(fileName, ".map");
        TheLevel->SetMap(TheTerrain->GetMap());
        TheLevel->Save(fileName);
    }

    TheFileSelector->GetWindow()->SetVisible(false);

    TheCamera->SetEnabled(true);
}


void GuiEditor::HandleExit(StringHash, VariantMap&)
{
    TheGUI->SetVisibleWindow(windowConfirmExit, true);
}


void GuiEditor::HandleExitOk(StringHash, VariantMap&)
{
    TheGuiEditor->SetVisible(false);
    TheCamera->SetEnabled(false);
    TheEditor->ClearScene();
    TheGUI->SetVisibleWindow(windowConfirmExit, false);
}


void GuiEditor::HandleExitCancel(StringHash, VariantMap&)
{
    TheGUI->SetVisibleWindow(windowConfirmExit, false);
}


void GuiEditor::HandleOptions(StringHash, VariantMap&)
{

}


void GuiEditor::HandleMouseDown(StringHash, VariantMap&)
{
    
}


void GuiEditor::HandleTerrainModeSelectChanged(StringHash, VariantMap& eventData) //-V2009
{
    int index = eventData[ItemSelected::P_SELECTION].GetInt();

    modeSelect = (ModeSelect)index;
}


void GuiEditor::HandleEditUndo(StringHash, VariantMap&)
{

}


void GuiEditor::HandleEditRedo(StringHash, VariantMap&)
{

}


void GuiEditor::HandleObjectsAdd(StringHash, VariantMap&)
{

}


bool GuiEditor::IsVisible()
{
    return panelMap->IsVisible();
}


void GuiEditor::SetVisible(bool visible)
{
    panelMap->SetVisible(visible);
    panelBottom->SetVisible(visible);
    panelMain->SetVisible(visible);
}

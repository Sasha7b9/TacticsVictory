#include <stdafx.h>


#include "GuiEditor.h"
#include "GUI/Elements/Tab.h"
#include "GUI/Elements/ButtonMain.h"
#include "GUI/Elements/Label.h"
#include "GUI/Elements/ButtonToggled.h"
#include "GUI/Elements/SliderWithTextAndButtons.h"
#include "GUI/Elements/DropDownListWithTextAndButton.h"
#include "GUI/Menu/PanelMap.h"
#include "GUI/Menu/PanelMain.h"
#include "GUI/Menu/MenuOptions.h"
#include "GUI/GUI.h"
#include "GUI/Menu/PanelBottom.h"
#include "Editor/Editor.h"
#include "Game/Level.h"
#include "Core/Camera.h"
#include "GlobalFunctions.h"


GuiEditor::GuiEditor(Context* context) :
    UIElement(context)
{
    SetFixedSize(gSet->GetInt(TV_SCREEN_WIDTH), gSet->GetInt(TV_SCREEN_HEIGHT));

    panelMap = new PanelMap(gContext);
    AddChild(panelMap);

    panelMain = new PanelMain(gContext);
    AddChild(panelMain);

    int width = 100;
    int height = 19;
    int dY = 27;
    int y = 10;
    int x = 10;

    // Tab "File"
    SharedPtr<Tab> tabFile(Tab::Create("File"));
    panelMain->AddTab(tabFile);

    SharedPtr<ButtonMain> btnFileOpen = tabFile->AddButton("Load", 10, y, width, height);
    btnFileOpen->SetHint("loadMapFromFile");
    SubscribeToEvent(btnFileOpen, Urho3D::E_RELEASED, HANDLER(GuiEditor, HandleFileLoad));

    SharedPtr<ButtonMain> btnFileSave = tabFile->AddButton("Save", 10, y += dY, width, height);
    btnFileSave->SetHint("saveMapToFile");
    SubscribeToEvent(btnFileSave, Urho3D::E_RELEASED, HANDLER(GuiEditor, HandleFileSave));

    // Tab "Edit"
    SharedPtr<Tab> tabEdit(Tab::Create("Edit"));
    panelMain->AddTab(tabEdit);

    y = 10;

    SharedPtr<ButtonMain> btnEditUndo = tabEdit->AddButton("Undo", x, y, width, height);
    btnEditUndo->SetHint("hintEditUndo");
    SubscribeToEvent(btnEditUndo, Urho3D::E_RELEASED, HANDLER(GuiEditor, HandleEditUndo));

    SharedPtr<ButtonMain>  btnEditRedo = tabEdit->AddButton("Redo", x, y += dY, width, height);
    btnEditRedo->SetHint("hintEditRedo");
    SubscribeToEvent(btnEditRedo, Urho3D::E_RELEASED, HANDLER(GuiEditor, HandleEditRedo));

    // Tab "Landscape"
    SharedPtr<Tab> tabLandscape(Tab::Create("Landscape"));
    panelMain->AddTab(tabLandscape);

    btnNewMap = tabLandscape->AddButton("New map", 10, y = 10, width, height);
    btnNewMap->SetHint("createNewMap");
    SubscribeToEvent(btnNewMap, Urho3D::E_RELEASED, HANDLER(GuiEditor, HandleButtonRelease));

    SharedPtr<ButtonMain> btnClearLandscape = tabLandscape->AddButton("Clear", 10, y += dY, width, height);
    btnClearLandscape->SetHint("clearLandscape");
    SubscribeToEvent(btnClearLandscape, Urho3D::E_RELEASED, HANDLER(GuiEditor, HandleLandscapeClearTerrain));

    SharedPtr<SliderWithTextAndButtons> sliderHeightDefault = tabLandscape->AddSlider("", -100, 100, 1, btnClearLandscape->GetPosition().x_ + btnClearLandscape->GetWidth() + 5, y - 2, 0, 20);
    sliderHeightDefault->SetValue(0);
    sliderHeightDefault->SetHint("hintSliderDefaultHeight");

    SharedPtr<SliderWithTextAndButtons> sliderSizeBrushX = tabLandscape->AddSlider("Brush X", 1, 10, 1, 10, y += dY, 75, 50);
    sliderSizeBrushX->SetValue(1);
    sliderSizeBrushX->SetHint("hintSliderSizeBrushX");

    SharedPtr<SliderWithTextAndButtons> sliderSizeBrushY = tabLandscape->AddSlider("Brush Y", 1, 10, 1, 10, y += dY, 75, 50);
    sliderSizeBrushY->SetValue(1);
    sliderSizeBrushY->SetHint("hintSliderSizeBrushY");

    char *items[] = { "Plane", "Edge" };
    SharedPtr<DropDownListWithTextAndButton> ddListModeSelect = tabLandscape->AddDDList("Mode select", 100, 80, 2, items, 10, y += dY);
    SubscribeToEvent(ddListModeSelect, Urho3D::E_ITEMSELECTED, HANDLER(GuiEditor, HandleLandscapeModeSelectChanged));

    // Tab "Objects"
    SharedPtr<Tab> tabObjects(Tab::Create("Objects"));
    panelMain->AddTab(tabObjects);

    y = 10;

    SharedPtr<ButtonMain> btnObjectsAdd = tabObjects->AddButton("Add", x, y, width, height);
    btnObjectsAdd->SetHint("hintObjectsAdd");
    SubscribeToEvent(btnObjectsAdd, Urho3D::E_RELEASED, HANDLER(GuiEditor, HandleObjectsAdd));

    // Panel bottom
    panelBottom = new PanelBottom(gContext);
    panelBottom->SetPosition(0, gSet->GetInt(TV_SCREEN_HEIGHT) - gSet->GetInt(TV_PANEL_BOTTOM_HEIGHT));

    width = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_WIDTH);
    height = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_HEIGHT);

    x = gSet->GetInt(TV_PANEL_MAP_WIDTH) / 2 - width / 2;
    y = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_Y);

    buttonInterface = panelBottom->AddButton("Interface", x, y, width, height);
    SubscribeToEvent(buttonInterface, Urho3D::E_RELEASED, HANDLER(GuiEditor, HandleButtonRelease));
    
    x = gSet->GetInt(TV_SCREEN_WIDTH) - 2 * width;
    buttonMenu = panelBottom->AddButton("Menu", x, y, width, height);
    SubscribeToEvent(buttonMenu, Urho3D::E_RELEASED, HANDLER(GuiEditor, HandleButtonRelease));

    AddChild(panelBottom);
    panelBottom->BringToFront();

    CreateWindows();

    SubscribeToEvent(Urho3D::E_KEYDOWN, HANDLER(GuiEditor, HandleKeyDown));
}

void GuiEditor::RegisterObject(Context *context)
{
    context->RegisterFactory<GuiEditor>("UI");

    COPY_BASE_ATTRIBUTES(UIElement);
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
    ButtonMain *button = (ButtonMain*)eventData[Urho3D::Released::P_ELEMENT].GetPtr();

    if (button == buttonInterface)
    {
        ToggleInterfacePanels();
    }
    else if (button == btnNewMap)
    {
        windowNewMap->SetVisible(!windowNewMap->IsVisible());
        if(windowNewMap->IsVisible())
        {
            gOpenedWindow.Push(windowNewMap);
            windowNewMap->BringToFront();
        }
    }
    else if(button == buttonMenu)
    {
        windowMenu->SetVisible(!windowMenu->IsVisible());
        if(windowMenu->IsVisible())
        {
            gOpenedWindow.Push(windowMenu);
            windowMenu->SetPosition(buttonMenu->GetPosition().x_, panelBottom->GetPosition().y_ - windowMenu->GetHeight());
            windowMenu->BringToFront();
        }
    }
}

bool GuiEditor::IntersectionX(ButtonMain *button, int x)
{
    return x >= button->GetPosition().x_ && x <= button->GetPosition().x_ + button->GetWidth();
}

bool GuiEditor::CheckOnDeadZoneForCursorBottomScreen(int x)
{
    return IntersectionX(buttonInterface, x) || IntersectionX(buttonMenu, x);
}

bool GuiEditor::IsInside(IntVector2 &position)
{
    return IsVisible() && 
        (
            panelBottom->IsInside(position, true) || 
            panelMain->IsInside(position, true) || 
            panelMap->IsInside(position, true) ||
            windowNewMap->IsInside(position, true)
        ) && 
        position.x_ > 0 && 
        position.x_ < gSet->GetInt(TV_SCREEN_WIDTH) - 1 &&
        position.y_ < gSet->GetInt(TV_SCREEN_HEIGHT) - 1;
}

void GuiEditor::CreateWindows()
{
    // window new map
    windowNewMap = new lWindow();
    SET_VERTICAL_LAYOUT_0_6(windowNewMap);

    windowNewMap->AddLabel("CreateNewMap");
    sliderSizeNewMapX = windowNewMap->AddSlider("Dimension X", 50, 250, 50);
    sliderSizeNewMapX->SetValue(150);
    sliderSizeNewMapY = windowNewMap->AddSlider("Dimension Y", 50, 250, 50);
    sliderSizeNewMapY->SetValue(150);
    SharedPtr<ButtonMain> buttonCreateMap = windowNewMap->AddButton("Create");
    SubscribeToEvent(buttonCreateMap, Urho3D::E_RELEASED, HANDLER(GuiEditor, HandleLandscapeCreateNewMap));

    windowNewMap->SetFixedSize(windowNewMap->GetSize());
    SetWindowInCenterScreen(windowNewMap);
    gUIRoot->AddChild(windowNewMap);
    windowNewMap->SetVisible(false);

    // window menu
    windowMenu = new lWindow();
    SET_VERTICAL_LAYOUT_0_0(windowMenu);

    SharedPtr<ButtonMain> buttonOptions = windowMenu->AddButton("Options");
    SubscribeToEvent(buttonOptions, Urho3D::E_RELEASED, HANDLER(GuiEditor, HandleOptions));
    SharedPtr<ButtonMain> buttonExit = windowMenu->AddButton("Exit");
    SubscribeToEvent(buttonExit, Urho3D::E_RELEASED, HANDLER(GuiEditor, HandleExit));

    windowMenu->SetFixedWidth(buttonMenu->GetWidth());
    windowMenu->SetFixedSize(windowMenu->GetSize());
    AddChild(windowMenu);
    windowMenu->SetVisible(false);

    // window confirm exit
    windowConfirmExit = new lWindow();
    SET_VERTICAL_LAYOUT_0_6(windowConfirmExit);

    SharedPtr<Label> label(Label::Create("Exit in main menu?"));
    windowConfirmExit->AddChild(label);

    SharedPtr<UIElement> layer(windowConfirmExit->CreateChild<UIElement>());
    SET_HORIZONTAL_LAYOUT_6_6(layer);

    SharedPtr<ButtonMain> buttonOk(new ButtonMain(layer, "Ok"));
    SubscribeToEvent(buttonOk, Urho3D::E_RELEASED, HANDLER(GuiEditor, HandleExitOk));

    SharedPtr<ButtonMain> buttonCancel(new ButtonMain(layer, "Cancel"));
    SubscribeToEvent(buttonCancel, Urho3D::E_RELEASED, HANDLER(GuiEditor, HandleExitCancel));

    windowConfirmExit->AddChild(layer);

    AddChild(windowConfirmExit);
    windowConfirmExit->SetVisible(false);
    SetWindowInCenterScreen(windowConfirmExit);

    SubscribeToEvent(Urho3D::E_MOUSEBUTTONDOWN, HANDLER(GuiEditor, HandleMouseDown));
}

void GuiEditor::HandleLandscapeCreateNewMap(StringHash, VariantMap&)
{
    Vector<Vector<float>> map = gLevel->CreateRandom((uint)sliderSizeNewMapY->GetValue(), (uint)sliderSizeNewMapX->GetValue());
    SAFE_DELETE(gTerrain);
    gTerrain = new Terrain(map);
    windowNewMap->SetVisible(false);

    gCamera->SetPosition({gLevel->GetWidth() / 2.0f, 20.0f, -(float)gLevel->GetHeight()}, {gLevel->GetWidth() / 2.0f, 0.0f, -(gLevel->GetHeight() / 2.0f)});
}

void GuiEditor::HandleLandscapeClearTerrain(StringHash, VariantMap&)
{
    for (uint row = 0; row < gTerrain->NumRows(); row++)
    {
        for (uint col = 0; col < gTerrain->NumCols(); col++)
        {
            gTerrain->SetHeight(row, col, 0.0f);
        }
    }

    gTerrain->Update();
}

void GuiEditor::HandleKeyDown(StringHash, VariantMap& eventData)
{
    if (!IsVisible())
    {
        return;
    }

    int key = eventData[Urho3D::KeyDown::P_KEY].GetInt();

    if (gFileSelector->GetWindow()->IsVisible())
    {
        if (key == Urho3D::KEY_ESC)
        {
            UnsubscribeFromEvent(gFileSelector, Urho3D::E_FILESELECTED);
            gFileSelector->GetWindow()->SetVisible(false);
            gCamera->SetEnabled(true);
        }
        return;
    }

    if (key == Urho3D::KEY_ESC)
    {
        if(!gOpenedWindow.Empty())
        {
            lWindow *window = gOpenedWindow.Back();
            window->SetVisible(false);
            gOpenedWindow.Remove(window);
        }
    }
    else if (key == Urho3D::KEY_I)
    {
        ToggleInterfacePanels();
    }
}

void GuiEditor::HandleFileLoad(StringHash, VariantMap&)
{
    gCamera->SetEnabled(false);

    Vector<String> filters;

    filters.Push("*.map");

    OpenFileSelector("Load landscape", "Load", "Cancel", filters);

    SubscribeToEvent(gFileSelector, Urho3D::E_FILESELECTED, HANDLER(GuiEditor, HandleFileSelectorLoadLandscape));
}

void GuiEditor::HandleFileSave(StringHash, VariantMap&)
{
    gCamera->SetEnabled(false);

    Vector<String> filters;

    filters.Push("*.map");

    OpenFileSelector("Save landscape", "Save", "Cancel", filters);

    SubscribeToEvent(gFileSelector, Urho3D::E_FILESELECTED, HANDLER(GuiEditor, HandleFileSelectorSaveLandscape));
}

void GuiEditor::HandleFileSelectorLoadLandscape(StringHash, VariantMap& eventData)
{
    UnsubscribeFromEvent(gFileSelector, Urho3D::E_FILESELECTED);

    bool ok = (bool)eventData[Urho3D::FileSelected::P_OK].GetBool();

    if(ok)
    {
        Vector<Vector<float>> map = gLevel->Load((char*)((String)eventData[Urho3D::FileSelected::P_FILENAME].GetString()).CString());
        SAFE_DELETE(gTerrain);
        gTerrain = new Terrain(map);
        gCamera->SetPosition({gLevel->GetWidth() / 2.0f, 20.0f, -(float)gLevel->GetHeight()}, {gLevel->GetWidth() / 2.0f, 0.0f, -(gLevel->GetHeight() / 2.0f)});
    }
    
    gFileSelector->GetWindow()->SetVisible(false);

    gCamera->SetEnabled(true);
}

void GuiEditor::HandleFileSelectorSaveLandscape(StringHash, VariantMap& eventData)
{
    UnsubscribeFromEvent(gFileSelector, Urho3D::E_FILESELECTED);

    bool ok = (bool)eventData[Urho3D::FileSelected::P_OK].GetBool();

    if (ok)
    {
        String fileName = (String)eventData[Urho3D::FileSelected::P_FILENAME].GetString();
        fileName = ReplaceExtension(fileName, ".map");
        gLevel->SetMap(gTerrain->GetMap());
        gLevel->Save(fileName);
    }

    gFileSelector->GetWindow()->SetVisible(false);

    gCamera->SetEnabled(true);
}

void GuiEditor::HandleExit(StringHash, VariantMap&)
{
    gGUI->SetVisibleWindow(windowConfirmExit, true);
}

void GuiEditor::HandleExitOk(StringHash, VariantMap&)
{
    gGuiEditor->SetVisible(false);
    gGUI->AddToScreen();
    gCamera->SetEnabled(false);
    gEditor->ClearScene();
    gGUI->SetVisibleWindow(windowConfirmExit, false);
}

void GuiEditor::HandleExitCancel(StringHash, VariantMap&)
{
    gGUI->SetVisibleWindow(windowConfirmExit, false);
}

void GuiEditor::HandleOptions(StringHash, VariantMap&)
{
    gGUI->SetVisibleWindow(gMenuOptions, true);
}

void GuiEditor::HandleMouseDown(StringHash, VariantMap&)
{
    
}

void GuiEditor::HandleLandscapeModeSelectChanged(StringHash, VariantMap& eventData)
{
    int index = eventData[Urho3D::ItemSelected::P_SELECTION].GetInt();

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

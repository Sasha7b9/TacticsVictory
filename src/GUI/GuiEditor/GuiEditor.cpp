#include <stdafx.h>


#include "GuiEditor.h"
#include "GUI/Elements/Tab.h"
#include "GUI/Elements/Button.h"
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


lGuiEditor::lGuiEditor(Context* context) :
    UIElement(context)
{
    SetFixedSize(gSet->GetInt(TV_SCREEN_WIDTH), gSet->GetInt(TV_SCREEN_HEIGHT));

    panelMap = new lPanelMap(gContext);
    AddChild(panelMap);

    panelMain = new lPanelMain(gContext);
    AddChild(panelMain);

    int width = 100;
    int height = 19;
    int dY = 30;
    int y = 10;

    // Tab "File"
    SharedPtr<lTab> tabFile(lTab::Create("File"));
    panelMain->AddTab(tabFile);

    SharedPtr<lButton> btnFileOpen = tabFile->AddButton("Load", 10, y, width, height);
    btnFileOpen->SetHint("loadMapFromFile");
    SubscribeToEvent(btnFileOpen, Urho3D::E_RELEASED, HANDLER(lGuiEditor, HandleButtonFileLoad));

    SharedPtr<lButton> btnFileSave = tabFile->AddButton("Save", 10, y += dY, width, height);
    btnFileSave->SetHint("saveMapToFile");
    SubscribeToEvent(btnFileSave, Urho3D::E_RELEASED, HANDLER(lGuiEditor, HandleButtonFileSave));

    // Tab "Landscape"
    SharedPtr<lTab> tabLandscape(lTab::Create("Landscape"));
    panelMain->AddTab(tabLandscape);

    btnNewMap = tabLandscape->AddButton("New map", 10, y = 10, width, height);
    btnNewMap->SetHint("createNewMap");
    SubscribeToEvent(btnNewMap, Urho3D::E_RELEASED, HANDLER(lGuiEditor, HandleButtonRelease));

    SharedPtr<lButton> btnClearLandscape = tabLandscape->AddButton("Clear", 10, y += dY, width, height);
    btnClearLandscape->SetHint("clearLandscape");
    SubscribeToEvent(btnClearLandscape, Urho3D::E_RELEASED, HANDLER(lGuiEditor, HandleClearTerrain));

    SharedPtr<lSliderWithTextAndButtons> sliderHeightDefault = tabLandscape->AddSlider("", -100, 100, 1, btnClearLandscape->GetPosition().x_ + btnClearLandscape->GetWidth() + 5, y - 2, 0, 20);
    sliderHeightDefault->SetValue(0);
    sliderHeightDefault->SetHint("hintSliderDefaultHeight");

    SharedPtr<lSliderWithTextAndButtons> sliderSizeBrushX = tabLandscape->AddSlider("Brush X", 1, 10, 1, 10, y += dY, 75, 50);
    sliderSizeBrushX->SetValue(1);
    sliderSizeBrushX->SetHint("hintSliderSizeBrushX");

    SharedPtr<lSliderWithTextAndButtons> sliderSizeBrushY = tabLandscape->AddSlider("Brush Y", 1, 10, 1, 10, y += dY, 75, 50);
    sliderSizeBrushY->SetValue(1);
    sliderSizeBrushY->SetHint("hintSliderSizeBrushY");

    char *items[] = { "Plane", "Edge" };
    SharedPtr<lDropDownListWithTextAndButton> ddListModeSelect = tabLandscape->AddDDList("Mode select", 100, 80, 2, items, 10, y += dY);
    SubscribeToEvent(ddListModeSelect, Urho3D::E_ITEMSELECTED, HANDLER(lGuiEditor, HandleModeSelectChanged));

    // Panel bottom
    panelBottom = new lPanelBottom(gContext);
    panelBottom->SetPosition(0, gSet->GetInt(TV_SCREEN_HEIGHT) - gSet->GetInt(TV_PANEL_BOTTOM_HEIGHT));

    width = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_WIDTH);
    height = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_HEIGHT);

    int x = gSet->GetInt(TV_PANEL_MAP_WIDTH) / 2 - width / 2;
    y = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_Y);

    buttonInterface = panelBottom->AddButton("Interface", x, y, width, height);
    SubscribeToEvent(buttonInterface, Urho3D::E_RELEASED, HANDLER(lGuiEditor, HandleButtonRelease));
    
    x = gSet->GetInt(TV_SCREEN_WIDTH) - 2 * width;
    buttonMenu = panelBottom->AddButton("Menu", x, y, width, height);
    SubscribeToEvent(buttonMenu, Urho3D::E_RELEASED, HANDLER(lGuiEditor, HandleButtonRelease));

    AddChild(panelBottom);
    panelBottom->BringToFront();

    CreateWindows();

    SubscribeToEvent(Urho3D::E_KEYDOWN, HANDLER(lGuiEditor, HandleKeyDown));
}

void lGuiEditor::RegisterObject(Context *context)
{
    context->RegisterFactory<lGuiEditor>("UI");

    COPY_BASE_ATTRIBUTES(UIElement);
}

void lGuiEditor::ToggleInterfacePanels()
{
    lLineTranslator2D::State stateMap = panelMap->GetTranslator()->GetState();
    lLineTranslator2D::State stateMain = panelMain->GetTranslator()->GetState();

    if(stateMap == lLineTranslator2D::State_PointStart && stateMain == lLineTranslator2D::State_PointStart)
    {
        panelMain->Toggle();
    }
    else if(stateMap == lLineTranslator2D::State_PointStart && stateMain == lLineTranslator2D::State_PointFinish)
    {
        panelMap->Toggle();
    }
    else if(stateMap == lLineTranslator2D::State_PointFinish && stateMain == lLineTranslator2D::State_PointFinish)
    {
        panelMap->Toggle();
        panelMain->Toggle();
    }
}

void lGuiEditor::HandleButtonRelease(StringHash, VariantMap &eventData)
{
    lButton *button = (lButton*)eventData[Urho3D::Released::P_ELEMENT].GetPtr();

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

bool lGuiEditor::IntersectionX(lButton *button, int x)
{
    return x >= button->GetPosition().x_ && x <= button->GetPosition().x_ + button->GetWidth();
}

bool lGuiEditor::CheckOnDeadZoneForCursorBottomScreen(int x)
{
    return IntersectionX(buttonInterface, x) || IntersectionX(buttonMenu, x);
}

bool lGuiEditor::IsInside(IntVector2 &position)
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

void lGuiEditor::CreateWindows()
{
    // window new map
    windowNewMap = new lWindow();
    SET_VERTICAL_LAYOUT_0_6(windowNewMap);

    windowNewMap->AddLabel("CreateNewMap");
    sliderSizeNewMapX = windowNewMap->AddSlider("Dimension X", 50, 250, 50);
    sliderSizeNewMapX->SetValue(150);
    sliderSizeNewMapY = windowNewMap->AddSlider("Dimension Y", 50, 250, 50);
    sliderSizeNewMapY->SetValue(150);
    SharedPtr<lButton> buttonCreateMap = windowNewMap->AddButton("Create");
    SubscribeToEvent(buttonCreateMap, Urho3D::E_RELEASED, HANDLER(lGuiEditor, HandleCreateNewMap));

    windowNewMap->SetFixedSize(windowNewMap->GetSize());
    SetWindowInCenterScreen(windowNewMap);
    gUIRoot->AddChild(windowNewMap);
    windowNewMap->SetVisible(false);

    // window menu
    windowMenu = new lWindow();
    SET_VERTICAL_LAYOUT_0_0(windowMenu);

    SharedPtr<lButton> buttonOptions = windowMenu->AddButton("Options");
    SubscribeToEvent(buttonOptions, Urho3D::E_RELEASED, HANDLER(lGuiEditor, HandleOptions));
    SharedPtr<lButton> buttonExit = windowMenu->AddButton("Exit");
    SubscribeToEvent(buttonExit, Urho3D::E_RELEASED, HANDLER(lGuiEditor, HandleExit));

    windowMenu->SetFixedWidth(buttonMenu->GetWidth());
    windowMenu->SetFixedSize(windowMenu->GetSize());
    AddChild(windowMenu);
    windowMenu->SetVisible(false);

    // window confirm exit
    windowConfirmExit = new lWindow();
    SET_VERTICAL_LAYOUT_0_6(windowConfirmExit);

    SharedPtr<lLabel> label(lLabel::Create("Exit in main menu?"));
    windowConfirmExit->AddChild(label);

    SharedPtr<UIElement> layer(windowConfirmExit->CreateChild<UIElement>());
    SET_HORIZONTAL_LAYOUT_6_6(layer);

    SharedPtr<lButton> buttonOk(new lButton(layer, "Ok"));
    SubscribeToEvent(buttonOk, Urho3D::E_RELEASED, HANDLER(lGuiEditor, HandleExitOk));

    SharedPtr<lButton> buttonCancel(new lButton(layer, "Cancel"));
    SubscribeToEvent(buttonCancel, Urho3D::E_RELEASED, HANDLER(lGuiEditor, HandleExitCancel));

    windowConfirmExit->AddChild(layer);

    AddChild(windowConfirmExit);
    windowConfirmExit->SetVisible(false);
    SetWindowInCenterScreen(windowConfirmExit);

    SubscribeToEvent(Urho3D::E_MOUSEBUTTONDOWN, HANDLER(lGuiEditor, HandleMouseDown));
}

void lGuiEditor::HandleCreateNewMap(StringHash, VariantMap&)
{
    Vector<Vector<float>> map = gLevel->CreateRandom((uint)sliderSizeNewMapY->GetValue(), (uint)sliderSizeNewMapX->GetValue());
    SAFE_DELETE(gTerrain);
    gTerrain = new lTerrain(map);
    windowNewMap->SetVisible(false);

    gCamera->SetPosition({gLevel->GetWidth() / 2.0f, 20.0f, -(float)gLevel->GetHeight()}, {gLevel->GetWidth() / 2.0f, 0.0f, -(gLevel->GetHeight() / 2.0f)});
}

void lGuiEditor::HandleClearTerrain(StringHash, VariantMap&)
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

void lGuiEditor::HandleKeyDown(StringHash, VariantMap& eventData)
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

void lGuiEditor::HandleButtonFileLoad(StringHash, VariantMap&)
{
    gCamera->SetEnabled(false);

    Vector<String> filters;

    filters.Push("*.map");

    OpenFileSelector("Load landscape", "Load", "Cancel", filters);

    SubscribeToEvent(gFileSelector, Urho3D::E_FILESELECTED, HANDLER(lGuiEditor, HandleFileSelectorLoadLandscape));
}

void lGuiEditor::HandleButtonFileSave(StringHash, VariantMap&)
{
    gCamera->SetEnabled(false);

    Vector<String> filters;

    filters.Push("*.map");

    OpenFileSelector("Save landscape", "Save", "Cancel", filters);

    SubscribeToEvent(gFileSelector, Urho3D::E_FILESELECTED, HANDLER(lGuiEditor, HandleFileSelectorSaveLandscape));
}

void lGuiEditor::HandleFileSelectorLoadLandscape(StringHash, VariantMap& eventData)
{
    UnsubscribeFromEvent(gFileSelector, Urho3D::E_FILESELECTED);

    bool ok = (bool)eventData[Urho3D::FileSelected::P_OK].GetBool();

    if(ok)
    {
        Vector<Vector<float>> map = gLevel->Load((char*)((String)eventData[Urho3D::FileSelected::P_FILENAME].GetString()).CString());
        SAFE_DELETE(gTerrain);
        gTerrain = new lTerrain(map);
        gCamera->SetPosition({gLevel->GetWidth() / 2.0f, 20.0f, -(float)gLevel->GetHeight()}, {gLevel->GetWidth() / 2.0f, 0.0f, -(gLevel->GetHeight() / 2.0f)});
    }
    
    gFileSelector->GetWindow()->SetVisible(false);

    gCamera->SetEnabled(true);
}

void lGuiEditor::HandleFileSelectorSaveLandscape(StringHash, VariantMap& eventData)
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

void lGuiEditor::HandleExit(StringHash, VariantMap&)
{
    gGUI->SetVisibleWindow(windowConfirmExit, true);
}

void lGuiEditor::HandleExitOk(StringHash, VariantMap&)
{
    gGuiEditor->SetVisible(false);
    gGUI->AddToScreen();
    gCamera->SetEnabled(false);
    gEditor->ClearScene();
    gGUI->SetVisibleWindow(windowConfirmExit, false);
}

void lGuiEditor::HandleExitCancel(StringHash, VariantMap&)
{
    gGUI->SetVisibleWindow(windowConfirmExit, false);
}

void lGuiEditor::HandleOptions(StringHash, VariantMap&)
{
    gGUI->SetVisibleWindow(gMenuOptions, true);
}

void lGuiEditor::HandleMouseDown(StringHash, VariantMap&)
{
    
}

void lGuiEditor::HandleModeSelectChanged(StringHash, VariantMap& eventData)
{
    int index = eventData[Urho3D::ItemSelected::P_SELECTION].GetInt();

    modeSelect = (ModeSelect)index;
}

#include <stdafx.h>


#include "GuiEditor.h"
#include "GUI/Elements/Tab.h"
#include "GUI/Elements/Button.h"
#include "GUI/Elements/Label.h"
#include "GUI/Elements/ButtonToggled.h"
#include "GUI/Elements/SliderWithTextAndButtons.h"
#include "GUI/Menu/PanelMap.h"
#include "GUI/Menu/PanelMain.h"
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
    int dY = 24;
    int y = 10;

    // Tab "File"
    SharedPtr<lTab> tabFile(lTab::Create("File"));
    panelMain->AddTab(tabFile);

    SharedPtr<lButton> btnFileOpen = tabFile->AddButton("Load", 10, y, width, height);
    btnFileOpen->SetHint("loadMapFromFile");
    SubscribeToEvent(btnFileOpen, Urho3D::E_RELEASED, HANDLER(lGuiEditor, HandleOpenMapFromFile));

    SharedPtr<lButton> btnFileSave = tabFile->AddButton("Save", 10, y += dY, width, height);
    btnFileSave->SetHint("saveMapToFile");
    SubscribeToEvent(btnFileSave, Urho3D::E_RELEASED, HANDLER(lGuiEditor, HandleSaveMapToFile));

    btnNewMap = tabFile->AddButton("New map", 10, y += dY, width, height);
    btnNewMap->SetHint("createNewMap");
    SubscribeToEvent(btnNewMap, Urho3D::E_RELEASED, HANDLER(lGuiEditor, HandleButtonRelease));

    SharedPtr<lButton> btnClearTerrain = tabFile->AddButton("Clear", 10, y += dY, width, height);
    btnClearTerrain->SetHint("clearLandscape");
    SubscribeToEvent(btnClearTerrain, Urho3D::E_RELEASED, HANDLER(lGuiEditor, HandleClearTerrain));

    // Tab "Edit"
    SharedPtr<lTab> tabEdit(lTab::Create("Edit"));
    panelMain->AddTab(tabEdit);

    panelBottom = new lPanelBottom(gContext);
    panelBottom->SetPosition(0, gSet->GetInt(TV_SCREEN_HEIGHT) - gSet->GetInt(TV_PANEL_BOTTOM_HEIGHT));

    width = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_WIDTH);
    height = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_HEIGHT);

    int x = gSet->GetInt(TV_PANEL_MAP_WIDTH) / 2 - width / 2;
    y = gSet->GetInt(TV_PANEL_BOTTOM_BUTTON_Y);

    buttonMap = panelBottom->AddButton("Map", x, y, width, height);
    SubscribeToEvent(buttonMap, Urho3D::E_RELEASED, HANDLER(lGuiEditor, HandleButtonRelease));

    x = (int)(gSet->GetInt(TV_PANEL_MAP_WIDTH) * 1.5f) - width / 2;
    buttonMainPanel = panelBottom->AddButton("Panel", x, y, width, height);
    SubscribeToEvent(buttonMainPanel, Urho3D::E_RELEASED, HANDLER(lGuiEditor, HandleButtonRelease));

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

void lGuiEditor::HandleButtonRelease(StringHash, VariantMap &eventData)
{
    lButton *button = (lButton*)eventData[Urho3D::Released::P_ELEMENT].GetPtr();

    if (button == buttonMap)
    {
        panelMap->Toggle();
    }
    else if (button == buttonMainPanel)
    {
        panelMain->Toggle();
    }
    else if (button == btnNewMap)
    {
        windowNewMap->SetVisible(!windowNewMap->IsVisible());
        if(windowNewMap->IsVisible())
        {
            windowNewMap->BringToFront();
        }
    }
}

bool lGuiEditor::IntersectionX(lButton *button, int x)
{
    return x >= button->GetPosition().x_ && x <= button->GetPosition().x_ + button->GetWidth();
}

bool lGuiEditor::CheckOnDeadZoneForCursorBottomScreen(int x)
{
    return IntersectionX(buttonMap, x) || IntersectionX(buttonMainPanel, x) || IntersectionX(buttonMenu, x);
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

void lGuiEditor::TogglePanelMain()
{
    panelMain->Toggle();
}

void lGuiEditor::TogglePanelMap()
{
    panelMap->Toggle();
}

void lGuiEditor::CreateWindows()
{
    windowNewMap = new lWindow();

    SET_VERTICAL_LAYOUT(windowNewMap);

    windowNewMap->AddLabel("CreateNewMap");
    SharedPtr<lSliderWithTextAndButtons> sliderX = windowNewMap->AddSlider("Dimension X", 0, 100);
    sliderX->SetValue(50);
    SharedPtr<lSliderWithTextAndButtons> sliderY = windowNewMap->AddSlider("Dimension Y", 0, 100);
    sliderY->SetValue(50);
    SharedPtr<lButton> buttonCreateMap = windowNewMap->AddButton("Create");
    SubscribeToEvent(buttonCreateMap, Urho3D::E_RELEASED, HANDLER(lGuiEditor, HandleCreateNewMap));

    windowNewMap->SetFixedSize(windowNewMap->GetSize());
    SetWindowInCenterScreen(windowNewMap);
    gUIRoot->AddChild(windowNewMap);
    windowNewMap->SetVisible(false);
}

void lGuiEditor::HandleCreateNewMap(StringHash, VariantMap&)
{
    Vector<Vector<float>> map = gLevel->CreateRandom(50, 100);
    SAFE_DELETE(gTerrain);
    gTerrain = new lTerrain(map);
    windowNewMap->SetVisible(false);

    gCamera->SetPosition({gLevel->GetWidth() / 2.0f, 20.0f, -(float)gLevel->GetHeight()}, {gLevel->GetWidth() / 2.0f, 0.0f, -(gLevel->GetHeight() / 2.0f)});
}

void lGuiEditor::HandleClearTerrain(StringHash, VariantMap&)
{
    gLevel->Clear();
    gTerrain->Clear();
}

void lGuiEditor::HandleKeyDown(StringHash, VariantMap& eventData)
{
    if (!IsVisible())
    {
        return;
    }

    int key = eventData[Urho3D::KeyDown::P_KEY].GetInt();

    if (key == Urho3D::KEY_ESC)
    {
        if (gGUI->MenuIsVisible())
        {
            gGUI->RemoveFromScreen();
            gCamera->SetEnabled(true);
            gScene->SetTimeScale(1.0f);
        }
        else if(gFileSelector)
        {
            UnsubscribeFromEvent(gFileSelector, Urho3D::E_FILESELECTED);
            SAFE_DELETE(gFileSelector);
        }
        else
        {
            if (windowNewMap->IsVisible())
            {
                windowNewMap->SetVisible(false);
            }
            else
            {
                gGUI->AddToScreen();
                gCamera->SetEnabled(false);
                gScene->SetTimeScale(0.0f);
            }
        }
        
    }
}

void lGuiEditor::HandleOpenMapFromFile(StringHash, VariantMap&)
{
    gFileSelector = new FileSelector(gContext);

    XMLFile *style = gCache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    gFileSelector->SetDefaultStyle(style);
    gFileSelector->SetButtonTexts("Ok", "Cancel");
    gFileSelector->GetWindow()->SetResizable(false);

    SetWindowInCenterScreen(gFileSelector->GetWindow());

    SubscribeToEvent(gFileSelector, Urho3D::E_FILESELECTED, HANDLER(lGuiEditor, HandleFileOpen));
}

void lGuiEditor::HandleSaveMapToFile(StringHash, VariantMap&)
{

}

void lGuiEditor::HandleFileOpen(StringHash, VariantMap& eventData)
{
    UnsubscribeFromEvent(gFileSelector, Urho3D::E_FILESELECTED);

    bool ok = (bool)eventData[Urho3D::FileSelected::P_OK].GetBool();

    if(ok)
    {

    }
    
    SAFE_DELETE(gFileSelector);
}
#include <stdafx.h>


#include "GUI.h"
#include "GUI/Elements/Tab.h"
#include "GUI/Elements/Button.h"
#include "GUI/Elements/ButtonToggled.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/Elements/Label.h"
#include "GUI/Elements/Slider.h"
#include "GUI/Elements/SliderInt.h"
#include "GUI/Elements/GovernorFloat.h"
#include "Core/Camera.h"
#include "GUI/Menu/MenuMain.h"
#include "GUI/Menu/MenuOptions.h"
#include "GUI/GuiGame/GuiGame.h"
#include "GUI/Menu/PanelBottom.h"
#include "GUI/Menu/PanelMap.h"
#include "GUI/Menu/PanelMain.h"
#include "GUI/Menu/Console.h"
#include "GUI/Menu/WindowVariables.h"
#include "GUI/Menu/MenuConfirmExit.h"
#include "GUI/GuiEditor/GuiEditor.h"
#include "GUI/Menu/MenuEvents.h"
#include "GlobalFunctions.h"


lGUI::lGUI() : Object(gContext)
{

}

lGUI::~lGUI()
{
    SAFE_DELETE(gCursor);
}

static void RegstrationObjects()
{
    lButton::RegisterObject(gContext);
    lButtonToggled::RegisterObject(gContext);
    lWindow::RegisterObject(gContext);
    lMenuMain::RegisterObject(gContext);
    lMenuOptions::RegisterObject(gContext);
    lMenuConfirmExit::RegisterObject(gContext);
    lTab::RegisterObject(gContext);
    lLabel::RegisterObject(gContext);
    vSlider::RegisterObject(gContext);
    lSliderInt::RegisterObject(gContext);
    vGovernorCell::RegisterObject(gContext);
    lGovernorFloat::RegisterObject(gContext);
    lPanelBottom::RegisterObject(gContext);
    lPanelMap::RegisterObject(gContext);
    lPanelMain::RegisterObject(gContext);
    lGuiEditor::RegisterObject(gContext);
}

static float GetPosCameraY()
{
    return gCamera->GetPosition().y_;
}

static void SetPosCameraY(float y)
{
    Vector3 position = gCamera->GetPosition();

    position.y_ = y;
    gCamera->SetPosition(position);
}

static float GetPosCameraX()
{
    return gCamera->GetPosition().x_;
}

static void SetPosCameraX(float x)
{
    Vector3 position = gCamera->GetPosition();

    position.x_ = x;
    gCamera->SetPosition(position);
}

static float GetPosCameraZ()
{
    return gCamera->GetPosition().z_;
}

static void SetPosCameraZ(float z)
{
    Vector3 position = gCamera->GetPosition();
    position.z_ = z;
    gCamera->SetPosition(position);
}

static float GetCameraPitch()
{
    Quaternion angle = gCamera->GetNode()->GetRotation();
    return angle.PitchAngle();
}

static float GetCameraYaw()
{
    Quaternion angle = gCamera->GetNode()->GetRotation();
    return angle.YawAngle();
}

void lGUI::Create()
{
    RegstrationObjects();

    gConsole = new lConsole(gContext);
    gUIRoot->AddChild(gConsole);

    gWindowVars = new lWindowVariables(gContext);
    gUIRoot->AddChild(gWindowVars);
    gWindowVars->SetVisible(false);
    gWindowVars->SetPosition(1000, 500);

    gWindowVars->AddFunctionFloat("Camera pos Y", GetPosCameraY, SetPosCameraY);
    gWindowVars->AddFunctionFloat("Camera pos X", GetPosCameraX, SetPosCameraX);
    gWindowVars->AddFunctionFloat("Camera pos Z", GetPosCameraZ, SetPosCameraZ);
    gWindowVars->AddFunctionFloat("Camera pitch", GetCameraPitch, nullptr);
    gWindowVars->AddFunctionFloat("Camera yaw", GetCameraYaw, nullptr);

    gLocalization->SetLanguage("en");

    gMenuMain = new lMenuMain(gContext);
    SetWindowInCenterScreen(gMenuMain);
    gUIRoot->AddChild(gMenuMain);
    SubscribeToEvent(gMenuMain, E_MENU, HANDLER(lGUI, HandleMenuEvent));

    gMenuOptions = new lMenuOptions(gContext);
    SetWindowInCenterScreen(gMenuOptions);
    gUIRoot->AddChild(gMenuOptions);
    SubscribeToEvent(gMenuOptions, E_MENU, HANDLER(lGUI, HandleMenuEvent));
    gMenuOptions->SetVisible(false);

    gGuiGame = new lGuiGame(gContext);
    gGuiGame->SetVisible(false);
    gUIRoot->AddChild(gGuiGame);

    gGuiEditor = new lGuiEditor(gContext);
    gGuiEditor->SetName("GuiEditor");
    gGuiEditor->SetVisible(false);
    gUIRoot->AddChild(gGuiEditor);

    gMenuConfirmExit = new lMenuConfirmExit(gContext);
    gUIRoot->AddChild(gMenuConfirmExit);
    SetWindowInCenterScreen(gMenuConfirmExit);
    gMenuConfirmExit->SetVisible(false);
    SubscribeToEvent(gMenuConfirmExit, E_MENU, HANDLER(lGUI, HandleMenuEvent));

    gCursor = new lCursor();

    gLocalization->SetLanguage(gSet->GetInt(TV_LANGUAGE) == 0 ? "en" : "ru");
}

bool lGUI::GheckOnDeadZoneForCursorBottomScreen(int x)
{
    if (gGuiGame->IsVisible())
    {
        return gGuiGame->CheckOnDeadZoneForCursorBottomScreen(x);
    }
    else if (gGuiEditor->IsVisible())
    {
        return gGuiEditor->CheckOnDeadZoneForCursorBottomScreen(x);
    }
    return false;
}

bool lGUI::MenuIsVisible()
{
    return gMenuMain->IsVisible() ||
        gMenuOptions->IsVisible() ||
        gMenuConfirmExit->IsVisible();
}

void lGUI::SetVisibleMenu(bool visible)
{
    gMenuMain->SetVisible(visible);
    gMenuOptions->SetVisible(visible);
}

void lGUI::SetVisibleMenu(lWindow *menuWindow, bool visible)
{
    menuWindow->SetVisible(visible);
    if(visible)
    {
        menuWindow->BringToFront();
    }
}

void lGUI::HandleMenuEvent(StringHash, VariantMap& eventData)
{
    uint action = eventData[MenuEvent::P_TYPE].GetUInt();

    if(action == MenuEvent_ExitInOS)
    {
        gEngine->Exit();
    }
    else if(action == MenuEvent_MenuOptionsOpen)
    {
        SetVisibleMenu(gMenuOptions, !gMenuOptions->IsVisible());
    }
    else if(action == MenuEvent_MenuOptionsClose)
    {
        gUIRoot->RemoveChild(gMenuOptions);
    }
}

void lGUI::RemoveFromScreen()
{
    shownMenuMain = gMenuMain->IsVisible();
    shownMenuOptions = gMenuOptions->IsVisible();

    gMenuMain->SetVisible(false);
    gMenuOptions->SetVisible(false);
}

void lGUI::AddToScreen()
{
    gMenuMain->SetVisible(shownMenuMain);
    gMenuOptions->SetVisible(shownMenuOptions);
}

bool lGUI::UnderCursor()
{
    IntVector2 pos = gCursor->GetCursor()->GetPosition();

    return gGuiEditor->IsInside(pos) || gGuiGame->IsInside(pos) || (gFileSelector->GetWindow()->IsVisible());
}

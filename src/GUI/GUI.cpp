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
#include "GUI/MenuGame/MenuGame.h"
#include "GUI/Menu/PanelBottom.h"
#include "GUI/Menu/PanelMap.h"
#include "GUI/Menu/PanelMain.h"
#include "GUI/Menu/Console.h"
#include "GUI/Menu/WindowVariables.h"
#include "GUI/MenuEditor/MenuEditor.h"


vGUI::vGUI() : Object(gContext)
{

}

vGUI::~vGUI()
{
    SAFE_DELETE(gCursor);
}

static void RegstrationObjects()
{
    vButton::RegisterObject(gContext);
    vButtonToggled::RegisterObject(gContext);
    vWindow::RegisterObject(gContext);
    vMenuMain::RegisterObject(gContext);
    vMenuOptions::RegisterObject(gContext);
    vTab::RegisterObject(gContext);
    vLabel::RegisterObject(gContext);
    vSlider::RegisterObject(gContext);
    vSliderInt::RegisterObject(gContext);
    vGovernorCell::RegisterObject(gContext);
    vGovernorFloat::RegisterObject(gContext);
    vPanelBottom::RegisterObject(gContext);
    vPanelMap::RegisterObject(gContext);
    vPanelMain::RegisterObject(gContext);
    vMenuEditor::RegisterObject(gContext);
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

void vGUI::Create()
{
    RegstrationObjects();

    gConsole = new vConsole(gContext);
    gUIRoot->AddChild(gConsole);

    gWindowVars = new vWindowVariables(gContext);
    gUIRoot->AddChild(gWindowVars);
    gWindowVars->SetVisible(false);
    gWindowVars->SetPosition(1000, 500);

    gWindowVars->AddFunctionFloat("Camera pos Y", GetPosCameraY, SetPosCameraY);
    gWindowVars->AddFunctionFloat("Camera pos X", GetPosCameraX, SetPosCameraX);
    gWindowVars->AddFunctionFloat("Camera pos Z", GetPosCameraZ, SetPosCameraZ);
    gWindowVars->AddFunctionFloat("Camera pitch", GetCameraPitch, nullptr);
    gWindowVars->AddFunctionFloat("Camera yaw", GetCameraYaw, nullptr);

    gMenuMain = new vMenuMain(gContext);
    gMenuMain->SetInCenterRect({0, 0, gSet->GetInt(TV_SCREEN_WIDTH), gSet->GetInt(TV_SCREEN_HEIGHT)});
    gUIRoot->AddChild(gMenuMain);
    SubscribeToEvent(gMenuMain, E_MENU, HANDLER(vGUI, HandleGuiEvent));

    gMenuOptions = new vMenuOptions(gContext);
    gMenuOptions->SetInCenterRect({0, 0, gSet->GetInt(TV_SCREEN_WIDTH), gSet->GetInt(TV_SCREEN_HEIGHT)});
    gUIRoot->AddChild(gMenuOptions);
    SubscribeToEvent(gMenuOptions, E_MENU, HANDLER(vGUI, HandleGuiEvent));
    gMenuOptions->SetVisible(false);

    gMenuGame = new vMenuGame(gContext);
    gMenuGame->SetVisible(false);
    gUIRoot->AddChild(gMenuGame);

    gMenuEditor = new vMenuEditor(gContext);
    gMenuEditor->SetVisible(false);
    gUIRoot->AddChild(gMenuEditor);

    gCursor = new vCursor();
}

bool vGUI::GheckOnDeadZoneForCursorBottomScreen(int x)
{
    if (gMenuGame->IsVisible())
    {
        return gMenuGame->CheckOnDeadZoneForCursorBottomScreen(x);
    }
    else if (gMenuEditor->IsVisible())
    {
        return gMenuEditor->CheckOnDeadZoneForCursorBottomScreen(x);
    }
    return false;
}

bool vGUI::MenuIsVisible()
{
    return gMenuMain->IsVisible() || gMenuOptions->IsVisible();
}

void vGUI::SetVisibleMenu(bool visible)
{
    gMenuMain->SetVisible(visible);
    gMenuOptions->SetVisible(visible);
}

void vGUI::SetVisibleMenu(vWindow *menuWindow, bool visible)
{
    menuWindow->SetVisible(visible);
    if(visible)
    {
        menuWindow->BringToFront();
    }
}

void vGUI::HandleGuiEvent(StringHash, VariantMap& eventData)
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

#include <stdafx.h>


static void RegstrationObjects()
{
    tvButton::RegisterObject(gContext);
    tvButtonToggled::RegisterObject(gContext);
    tvWindow::RegisterObject(gContext);
    tvMenu::RegisterObject(gContext);
    tvMenuMain::RegisterObject(gContext);
    tvMenuOptions::RegisterObject(gContext);
    tvTab::RegisterObject(gContext);
    tvLabel::RegisterObject(gContext);
    tvSlider::RegisterObject(gContext);
    tvSliderInt::RegisterObject(gContext);
    GovernorCell::RegisterObject(gContext);
    tvGovernorFloat::RegisterObject(gContext);
    tvPanelBottom::RegisterObject(gContext);
    tvPanelMap::RegisterObject(gContext);
    tvPanelMain::RegisterObject(gContext);
    tvMenuEditor::RegisterObject(gContext);
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

void tvGUI::Create()
{
    RegstrationObjects();

    gConsole = new tvConsole(gContext);
    gUIRoot->AddChild(gConsole);

    gWindowVars = new tvWindowVariables(gContext);
    gUIRoot->AddChild(gWindowVars);
    gWindowVars->SetVisible(false);
    gWindowVars->SetPosition(1000, 500);

    gWindowVars->AddFunctionFloat("Camera pos Y", GetPosCameraY, SetPosCameraY);
    gWindowVars->AddFunctionFloat("Camera pos X", GetPosCameraX, SetPosCameraX);
    gWindowVars->AddFunctionFloat("Camera pos Z", GetPosCameraZ, SetPosCameraZ);
    gWindowVars->AddFunctionFloat("Camera pitch", GetCameraPitch, nullptr);
    gWindowVars->AddFunctionFloat("Camera yaw", GetCameraYaw, nullptr);

    gMenu = new tvMenu(gContext);
    gUIRoot->AddChild(gMenu);

    gMenuGame = new tvMenuGame(gContext);
    gMenuGame->SetVisible(false);
    gUIRoot->AddChild(gMenuGame);

    gMenuEditor = new tvMenuEditor(gContext);
    gMenuEditor->SetVisible(false);
    gUIRoot->AddChild(gMenuEditor);

    gCursor = new tvCursor();
}

bool tvGUI::GheckOnDeadZoneForCursorBottomScreen(int x)
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
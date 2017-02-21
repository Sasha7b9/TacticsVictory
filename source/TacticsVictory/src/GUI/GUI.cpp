#include <stdafx.h>


#include "GUI.h"
#include "GUI/Elements/Tab.h"
#include "GUI/Elements/ButtonMain.h"
#include "GUI/Elements/ButtonSwitch.h"
#include "GUI/Elements/ButtonToggled.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/Elements/DropDownListWithTextAndButton.h"
#include "GUI/Elements/Label.h"
#include "GUI/Elements/Slider.h"
#include "GUI/Elements/SliderInt.h"
#include "GUI/Elements/GovernorFloat.h"
#include "GUI/Elements/SliderWithTextAndButtons.h"
#include "Core/Camera.h"
#include "GUI/Menu/MenuMain.h"
#include "GUI/Menu/MenuOptions.h"
#include "GUI/GuiGame/GuiGame.h"
#include "GUI/Menu/PanelBottom.h"
#include "GUI/Menu/PanelMap.h"
#include "GUI/Menu/PanelMain.h"
#include "GUI/Menu/Console.h"
#include "GUI/Menu/WindowVariables.h"
#include "GUI/Menu/WindowConfirmExit.h"
#include "GUI/GuiEditor/GuiEditor.h"
#include "GUI/Menu/MenuEvents.h"
#include "GlobalFunctions.h"


GUI::GUI() : Object(gContext)
{

}

GUI::~GUI()
{
    SAFE_DELETE(gCursor);
    SAFE_DELETE(gGuiGame);
    SAFE_DELETE(gGuiEditor);
}

static void RegstrationObjects()
{
    ButtonMain::RegisterObject();
    ButtonSwitch::RegisterObject();
    ButtonToggled::RegisterObject();
    WindowRTS::RegisterObject();
    MenuMain::RegisterObject();
    MenuOptions::RegisterObject();
    WindowConfirmExit::RegisterObject();
    Tab::RegisterObject();
    Label::RegisterObject();
    lSlider::RegisterObject();
    SliderInt::RegisterObject();
    GovernorCell::RegisterObject();
    GovernorFloat::RegisterObject();
    PanelBottom::RegisterObject();
    PanelMap::RegisterObject();
    PanelMain::RegisterObject();
    SliderWithTextAndButtons::RegisterObject();
    DropDownListWithTextAndButton::RegisterObject();
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

void GUI::Create()
{
    RegstrationObjects();

    gMenuMain = new MenuMain(gContext);
    SetWindowInCenterScreen(gMenuMain);
    gUIRoot->AddChild(gMenuMain);
    SubscribeToEvent(gMenuMain, E_MENU, URHO3D_HANDLER(GUI, HandleMenuEvent));

    gConsole = new ConsoleRTS(gContext);
    gUIRoot->AddChild(gConsole);

    gWindowVars = new WindowVariables(gContext);
    gUIRoot->AddChild(gWindowVars);
    gWindowVars->SetVisible(false);
    gWindowVars->SetPosition(1000, 500);

    gWindowVars->AddFunctionFloat("Camera pos Y", GetPosCameraY, SetPosCameraY);
    gWindowVars->AddFunctionFloat("Camera pos X", GetPosCameraX, SetPosCameraX);
    gWindowVars->AddFunctionFloat("Camera pos Z", GetPosCameraZ, SetPosCameraZ);
    gWindowVars->AddFunctionFloat("Camera pitch", GetCameraPitch, nullptr);
    gWindowVars->AddFunctionFloat("Camera yaw", GetCameraYaw, nullptr);

    gLocalization->SetLanguage("en");

    gMenuOptions = new MenuOptions(gContext);
    SetWindowInCenterScreen(gMenuOptions);
    gUIRoot->AddChild(gMenuOptions);
    SubscribeToEvent(gMenuOptions, E_MENU, URHO3D_HANDLER(GUI, HandleMenuEvent));
    gMenuOptions->SetVisible(false);

    gGuiGame = new GuiGame(gContext);
    gGuiGame->SetVisible(false);

    gGuiEditor = new GuiEditor(gContext);
    gGuiEditor->SetVisible(false);

    gWindowConfirmExit = new WindowConfirmExit(gContext);
    gUIRoot->AddChild(gWindowConfirmExit);
    SetWindowInCenterScreen(gWindowConfirmExit);
    gWindowConfirmExit->SetVisible(false);
    SubscribeToEvent(gWindowConfirmExit, E_MENU, URHO3D_HANDLER(GUI, HandleMenuEvent));

    gCursor = new CursorRTS();

    gLocalization->SetLanguage(gSet->GetInt(TV_LANGUAGE) == 0 ? "en" : "ru");
}

bool GUI::GheckOnDeadZoneForCursorBottomScreen(int x)
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

bool GUI::MenuIsVisible()
{
    return gMenuMain->IsVisible() ||
        gMenuOptions->IsVisible() ||
        gWindowConfirmExit->IsVisible();
}

void GUI::SetVisibleMenu(bool visible)
{
    visible ? gMenuMain->SetEnabled() : gMenuMain->SetDisabled();
    gMenuOptions->SetVisible(visible);
}

void GUI::SetVisibleMenu(WindowRTS *menuWindow, bool visible)
{
    menuWindow->SetVisible(visible);
    if(visible)
    {
        menuWindow->BringToFront();
    }
}

void GUI::HandleMenuEvent(StringHash, VariantMap& eventData)
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

void GUI::RemoveFromScreen()
{
    shownMenuMain = gMenuMain->IsVisible();
    shownMenuOptions = gMenuOptions->IsVisible();

    gMenuMain->SetDisabled();
    gMenuOptions->SetVisible(false);
}

void GUI::AddToScreen()
{
    shownMenuMain ? gMenuMain->SetEnabled() : gMenuMain->SetDisabled();
    gMenuOptions->SetVisible(shownMenuOptions);
}

bool GUI::UnderCursor()
{
    PODVector<UIElement*> elements;
    gUIRoot->GetChildren(elements);

    for(auto elem : elements)
    {
        if(elem->GetName() != "Cursor" && elem->IsVisible() && elem->IsInside(gCursor->GetCursor()->GetPosition(), true))
        {
            return true;
        }
    }

    return false;
}

void GUI::SetVisibleWindow(WindowRTS *window, bool visible)
{
    window->SetVisible(visible);
    if(visible)
    {
        while(!gOpenedWindow.Empty())
        {
            WindowRTS *window = gOpenedWindow.Back();
            window->SetVisible(false);
            gOpenedWindow.Remove(window);
        }
        gOpenedWindow.Push(window);
    }
    else
    {
        gOpenedWindow.Remove(window);
    }
}

void GUI::SetUnvisibleAllWindows()
{
    while(!gOpenedWindow.Empty())
    {
        WindowRTS *window = gOpenedWindow.Back();
        window->SetVisible(false);
        gOpenedWindow.Remove(window);
    }
}

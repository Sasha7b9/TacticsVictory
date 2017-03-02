#include <stdafx.h>
#include "GUI.h"
#include "GUI/Controls/Tab.h"
#include "GUI/Controls/Button.h"
#include "GUI/Controls/ButtonSwitch.h"
#include "GUI/Controls/ButtonToggled.h"
#include "GUI/Cursor.h"
#include "GUI/Controls/DropDownListWithTextAndButton.h"
#include "GUI/Controls/Label.h"
#include "GUI/Controls/Slider.h"
#include "GUI/Controls/SliderInt.h"
#include "GUI/Controls/GovernorFloat.h"
#include "GUI/Controls/SliderWithTextAndButtons.h"
#include "Core/Camera.h"
#include "GUI/Menu/MenuMain.h"
#include "GUI/Menu/MenuStart.h"
#include "GUI/Menu/MenuOptions.h"
#include "GUI/GuiGame/GuiGame.h"
#include "GUI/Panels/PanelBottom.h"
#include "GUI/Panels/PanelMap.h"
#include "GUI/Panels/PanelMain.h"
#include "GUI/Windows/Console.h"
#include "GUI/Windows/WindowVariables.h"
#include "GUI/Menu/MenuConfirmExit.h"
#include "GUI/GuiEditor/GuiEditor.h"
#include "GUI/Menu/MenuEvents.h"
#include "GlobalFunctions.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI() : Object(gContext)
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
GUI::~GUI()
{
    SAFE_DELETE(gCursor);
    SAFE_DELETE(gGuiGame);
    SAFE_DELETE(gGuiEditor);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GUI::RegistrationObjects()
{
    ButtonRTS::RegisterObject();
    ButtonSwitch::RegisterObject();
    ButtonToggled::RegisterObject();
    WindowRTS::RegisterObject();
    MenuMain::RegisterObject();
    MenuOptions::RegisterObject();
    MenuConfirmExit::RegisterObject();
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
static float GetPosCameraY()
{
    return gCamera->GetPosition().y_;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void SetPosCameraY(float y)
{
    Vector3 position = gCamera->GetPosition();

    position.y_ = y;
    gCamera->SetPosition(position);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static float GetPosCameraX()
{
    return gCamera->GetPosition().x_;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void SetPosCameraX(float x)
{
    Vector3 position = gCamera->GetPosition();

    position.x_ = x;
    gCamera->SetPosition(position);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static float GetPosCameraZ()
{
    return gCamera->GetPosition().z_;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void SetPosCameraZ(float z)
{
    Vector3 position = gCamera->GetPosition();
    position.z_ = z;
    gCamera->SetPosition(position);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static float GetCameraPitch()
{
    Quaternion angle = gCamera->GetNode()->GetRotation();
    return angle.PitchAngle();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static float GetCameraYaw()
{
    Quaternion angle = gCamera->GetNode()->GetRotation();
    return angle.YawAngle();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GUI::Create()
{
    gMenuStart = new MenuStart();
    SetWindowInCenterScreen(gMenuStart);
    gUIRoot->AddChild(gMenuStart);

    gMenuMain = new MenuMain();
    SetWindowInCenterScreen(gMenuMain);
    gUIRoot->AddChild(gMenuMain);
    SubscribeToEvent(gMenuMain, E_MENU, URHO3D_HANDLER(GUI, HandleMenuEvent));
    gMenuMain->SetVisible(false);

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

    gMenuConfirmExit = new MenuConfirmExit(gContext);
    gUIRoot->AddChild(gMenuConfirmExit);
    SetWindowInCenterScreen(gMenuConfirmExit);
    gMenuConfirmExit->SetVisible(false);
    SubscribeToEvent(gMenuConfirmExit, E_MENU, URHO3D_HANDLER(GUI, HandleMenuEvent));

    gCursor = new CursorRTS();

    gLocalization->SetLanguage(gSet->GetInt(TV_LANGUAGE) == 0 ? "en" : "ru");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
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
        gMenuConfirmExit->IsVisible();
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

    for(UIElement *elem : elements)
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
            window = gOpenedWindow.Back();
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

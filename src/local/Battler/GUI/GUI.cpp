// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "GUI.h"
#include "GlobalFunctions.h"
#include "Core/Camera.h"
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
#include "GUI/Menu/MenuStart.h"
#include "GUI/Menu/MenuGame.h"
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
#include "GUI/Menu/MenuAboutMe.h"
#include "Network/Client.h"
#include "Network/Server.h"



GUI::GUI() : Object(gContext)
{
    RegistrationObjects();
    Create();
}


GUI::~GUI()
{
    SAFE_DELETE(gCursor); //-V809
    SAFE_DELETE(gGuiGame); //-V809
    SAFE_DELETE(gGuiEditor); //-V809
}


void GUI::RegistrationObjects()
{
    ButtonRTS::RegisterObject();
    ButtonSwitch::RegisterObject();
    ButtonToggled::RegisterObject();
    WindowRTS::RegisterObject();
    MenuGame::RegisterObject();
    MenuOptions::RegisterObject();
    MenuConfirmExit::RegisterObject();
    MenuAboutMe::RegisterObject();
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


static float GetSpeedNetIN()
{
    if(gClient->IsConnected())
    {
        Connection *connection = gClient->GetServerConnection();
        return connection->GetBytesInPerSec() / 1e3f;
    }
    else
    {
        Vector<SharedPtr<Connection>> connections = gServer->GetConnections();
        if(connections.Size())
        {
            float speed = 0.0f;
            for(Connection *connection : connections)
            {
                speed += connection->GetBytesInPerSec();
            }
            return speed / 1e3f;
        }
    }
    return 0.0f;
}


static float GetSpeedNetOUT()
{
    if(gClient->GetServerConnection())
    {
        Connection *connection = gClient->GetServerConnection();
        return connection->GetBytesOutPerSec() / 1e3f;
    }
    else
    {
        Vector<SharedPtr<Connection>> connections = gServer->GetConnections();
        if(connections.Size())
        {
            float speed = 0.0f;
            for(Connection *connection : connections)
            {
                speed += connection->GetBytesOutPerSec();
            }
            return speed / 1e3f;
        }
    }
    return 0.0f;
}


void GUI::Create()
{
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
    gWindowVars->AddFunctionFloat("Net speed in, kB/s", GetSpeedNetIN, nullptr);
    gWindowVars->AddFunctionFloat("Net speec out, kB/s", GetSpeedNetOUT, nullptr);

    gLocalization->SetLanguage("en");

    gGuiGame = new GuiGame(gContext);
    gGuiGame->SetVisible(false);

    gGuiEditor = new GuiEditor(gContext);
    gGuiEditor->SetVisible(false);

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

// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
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



GUI::GUI() : Object(TheContext)
{
    RegistrationObjects();
    Create();
}


GUI::~GUI()
{
    SAFE_DELETE(TheCursor); //-V809
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
    return TheCamera->GetPosition().y_;
}


static void SetPosCameraY(float y)
{
    Vector3 position = TheCamera->GetPosition();

    position.y_ = y;
    TheCamera->SetPosition(position);
}


static float GetPosCameraX()
{
    return TheCamera->GetPosition().x_;
}


static void SetPosCameraX(float x)
{
    Vector3 position = TheCamera->GetPosition();

    position.x_ = x;
    TheCamera->SetPosition(position);
}


static float GetPosCameraZ()
{
    return TheCamera->GetPosition().z_;
}


static void SetPosCameraZ(float z)
{
    Vector3 position = TheCamera->GetPosition();
    position.z_ = z;
    TheCamera->SetPosition(position);
}


static float GetCameraPitch()
{
    Quaternion angle = TheCamera->GetNode()->GetRotation();
    return angle.PitchAngle();
}


static float GetCameraYaw()
{
    Quaternion angle = TheCamera->GetNode()->GetRotation();
    return angle.YawAngle();
}


static float GetSpeedNetIN()
{
    if(TheClient->IsConnected())
    {
        Connection *connection = TheClient->GetServerConnection();
        return connection->GetBytesInPerSec() / 1e3f;
    }
    else
    {
        Vector<SharedPtr<Connection>> connections = TheServer->GetConnections();
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
    if(TheClient->GetServerConnection())
    {
        Connection *connection = TheClient->GetServerConnection();
        return connection->GetBytesOutPerSec() / 1e3f;
    }
    else
    {
        Vector<SharedPtr<Connection>> connections = TheServer->GetConnections();
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
    gConsole = new ConsoleRTS(TheContext);
    TheUIRoot->AddChild(gConsole);

    gWindowVars = new WindowVariables(TheContext);
    TheUIRoot->AddChild(gWindowVars);
    gWindowVars->SetVisible(false);
    gWindowVars->SetPosition(1000, 500);

    gWindowVars->AddFunctionFloat("Camera pos Y", GetPosCameraY, SetPosCameraY);
    gWindowVars->AddFunctionFloat("Camera pos X", GetPosCameraX, SetPosCameraX);
    gWindowVars->AddFunctionFloat("Camera pos Z", GetPosCameraZ, SetPosCameraZ);
    gWindowVars->AddFunctionFloat("Camera pitch", GetCameraPitch, nullptr);
    gWindowVars->AddFunctionFloat("Camera yaw", GetCameraYaw, nullptr);
    gWindowVars->AddFunctionFloat("Net speed in, kB/s", GetSpeedNetIN, nullptr);
    gWindowVars->AddFunctionFloat("Net speec out, kB/s", GetSpeedNetOUT, nullptr);

    TheLocalization->SetLanguage("en");

    gGuiGame = new GuiGame(TheContext);
    gGuiGame->SetVisible(false);

    gGuiEditor = new GuiEditor(TheContext);
    gGuiEditor->SetVisible(false);

    TheCursor = new CursorRTS();

    TheLocalization->SetLanguage(TheSet->GetInt(TV_LANGUAGE) == 0 ? "en" : "ru");
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
    TheUIRoot->GetChildren(elements);

    for(UIElement *elem : elements)
    {
        if(elem->GetName() != "Cursor" && elem->IsVisible() && elem->IsInside(TheCursor->GetCursor()->GetPosition(), true))
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

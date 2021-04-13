// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"
#include "GUI/Cursor_.h"
#include "GUI/GUI.h"
#include "GUI/Controls/DropDownListWithTextAndButton_.h"
#include "GUI/Controls/GovernorFloat_.h"
#include "GUI/Controls/Label_.h"
#include "GUI/Controls/Buttons/ButtonSwitch_.h"
#include "GUI/Controls/Buttons/ButtonToggled_.h"
#include "GUI/Controls/Sliders/Slider_.h"
#include "GUI/Controls/Sliders/SliderInt_.h"
#include "GUI/Controls/Sliders/SliderWithTextAndButtons_.h"
#include "GUI/Menu/PageConfirmExit_.h"
#include "GUI/Windows/Console_.h"
#include "GUI/Windows/WindowVariables_.h"
#include "Scene/Cameras/Camera_.h"


GUI::GUI(GUI **self) : GUIT((GUIT **)self)
{
    Create();

    *self = this;
}


GUI::~GUI()
{
}


static float GetPosCameraY()
{
    if (TheCamera == nullptr)
    {
        return 0.0f;
    }

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
//    if(TheClient->IsConnected())
//    {
//        Connection *connection = TheClient->GetServerConnection();
//        return connection->GetBytesInPerSec() / 1e3f;
//    }
//    else
//    {
//        Vector<SharedPtr<Connection>> connections = TheServer->GetConnections();
//        if(connections.Size())
//        {
//            float speed = 0.0f;
//            for(Connection *connection : connections)
//            {
//                speed += connection->GetBytesInPerSec();
//            }
//            return speed / 1e3f;
//        }
//    }

    return 0.0f;
}


static float GetSpeedNetOUT()
{
//    if(TheClient->GetServerConnection())
//    {
//        Connection *connection = TheClient->GetServerConnection();
//        return connection->GetBytesOutPerSec() / 1e3f;
//    }
//    else
//    {
//        Vector<SharedPtr<Connection>> connections = TheServer->GetConnections();
//        if(connections.Size())
//        {
//            float speed = 0.0f;
//            for(Connection *connection : connections)
//            {
//                speed += connection->GetBytesOutPerSec();
//            }
//            return speed / 1e3f;
//        }
//    }

    return 0.0f;
}


void GUI::Create()
{
    TheConsole = new ConsoleT();
    TheUIRoot->AddChild(TheConsole);

    TheWindowVars = new WindowVariables();
    TheUIRoot->AddChild(TheWindowVars);
    TheWindowVars->SetVisible(false);
    TheWindowVars->SetPosition(1000, 500);

    TheWindowVars->AddFunctionFloat("Camera pos Y", GetPosCameraY, SetPosCameraY);
    TheWindowVars->AddFunctionFloat("Camera pos X", GetPosCameraX, SetPosCameraX);
    TheWindowVars->AddFunctionFloat("Camera pos Z", GetPosCameraZ, SetPosCameraZ);
    TheWindowVars->AddFunctionFloat("Camera pitch", GetCameraPitch, nullptr);
    TheWindowVars->AddFunctionFloat("Camera yaw", GetCameraYaw, nullptr);
    TheWindowVars->AddFunctionFloat("Net speed in, kB/s", GetSpeedNetIN, nullptr);
    TheWindowVars->AddFunctionFloat("Net speed out, kB/s", GetSpeedNetOUT, nullptr);

    TheLocalization->SetLanguage("en");

    TheCursor = TheUIRoot->CreateChild<CursorT>("CursorT");

    TheLocalization->SetLanguage(TheSettings.GetInt("language") == 0 ? "en" : "ru");
}


void GUI::SetVisibleWindow(WindowT *window, bool visible)
{
    window->SetVisible(visible);
    if(visible)
    {
        while(!TheOpenedWindow.Empty())
        {
            window = TheOpenedWindow.Back();
            window->SetVisible(false);
            TheOpenedWindow.Remove(window);
        }
        TheOpenedWindow.Push(window);
    }
    else
    {
        TheOpenedWindow.Remove(window);
    }
}


void GUI::SetUnvisibleAllWindows()
{
    while(!TheOpenedWindow.Empty())
    {
        WindowT *window = TheOpenedWindow.Back();
        window->SetVisible(false);
        TheOpenedWindow.Remove(window);
    }
}

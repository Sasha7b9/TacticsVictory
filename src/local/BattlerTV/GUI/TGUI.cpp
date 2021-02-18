// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/TCursor.h"
#include "GUI/TGUI.h"
#include "GUI/Controls/_TButtonSwitch.h"
#include "GUI/Controls/_TButtonToggled.h"
#include "GUI/Controls/_TDropDownListWithTextAndButton.h"
#include "GUI/Controls/_TGovernorFloat.h"
#include "GUI/Controls/_TSlider.h"
#include "GUI/Controls/_TSliderInt.h"
#include "GUI/Controls/_TSliderWithTextAndButtons.h"
#include "GUI/Controls/_TTab.h"
#include "GUI/GuiEditor/TGuiEditor.h"


GUI::GUI() : Object(TheContext)
{
    RegistrationObjects();
    Create();
}


GUI::~GUI()
{
    SAFE_DELETE(TheCursor); //-V809
    SAFE_DELETE(TheGuiGame); //-V809
    SAFE_DELETE(TheGuiEditor); //-V809
}


void GUI::RegistrationObjects()
{
    ButtonTV::RegisterObject();
    ButtonSwitch::RegisterObject();
    ButtonToggled::RegisterObject();
    TWindow::RegisterObject();
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
    TheConsole = new TConsole();
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
    TheWindowVars->AddFunctionFloat("Net speec out, kB/s", GetSpeedNetOUT, nullptr);

    TheLocalization->SetLanguage("en");

    TheGuiGame = new GuiGame();
    TheGuiGame->SetVisible(false);

    TheGuiEditor = new GuiEditor();
    TheGuiEditor->SetVisible(false);

    TheCursor = new TCursor();

    TheLocalization->SetLanguage(TheSet->GetInt(TV_LANGUAGE) == 0 ? "en" : "ru");
}


bool GUI::GheckOnDeadZoneForCursorBottomScreen(int x)
{
    if (TheGuiGame->IsVisible())
    {
        return TheGuiGame->CheckOnDeadZoneForCursorBottomScreen(x);
    }
    else if (TheGuiEditor->IsVisible())
    {
        return TheGuiEditor->CheckOnDeadZoneForCursorBottomScreen(x);
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


void GUI::SetVisibleWindow(TWindow *window, bool visible)
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
        TWindow *window = TheOpenedWindow.Back();
        window->SetVisible(false);
        TheOpenedWindow.Remove(window);
    }
}

// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "Input.h"
#include "Mouse.h"
#include "GUI/Widgets/Console.h"


using namespace Pi;


void Input::Init()
{
    TheInputMgr->AddAction(new NavigationAction(PiTypeAction::Left, CameraRTS::E::MoveLeft));
    TheInputMgr->AddAction(new NavigationAction(PiTypeAction::Right, CameraRTS::E::MoveRight));
    TheInputMgr->AddAction(new NavigationAction(PiTypeAction::Forward, CameraRTS::E::MovekForward));
    TheInputMgr->AddAction(new NavigationAction(PiTypeAction::Backward, CameraRTS::E::MoveBackward));
    TheInputMgr->AddAction(new NavigationAction(PiTypeAction::RotLeft, CameraRTS::E::RotateLeft));
    TheInputMgr->AddAction(new NavigationAction(PiTypeAction::RotRight, CameraRTS::E::RotateRight));
    TheInputMgr->AddAction(new NavigationAction(PiTypeAction::RotTop, CameraRTS::E::RotateTop));
    TheInputMgr->AddAction(new NavigationAction(PiTypeAction::RotDown, CameraRTS::E::RotateDown));
    TheInputMgr->AddAction(new NavigationAction(PiTypeAction::ZoomIn, CameraRTS::E::ZoomIn));
    TheInputMgr->AddAction(new NavigationAction(PiTypeAction::ZoomOut, CameraRTS::E::ZoomOut));
    TheInputMgr->AddAction(new NavigationAction(PiTypeAction::Center, CameraRTS::E::MoveCenter));

    TheInputMgr->AddAction(new KeyboardAction(PiTypeAction::F1));
    TheInputMgr->AddAction(new KeyboardAction(PiTypeAction::F2));
    TheInputMgr->AddAction(new KeyboardAction(PiTypeAction::Esc));

    TheInputMgr->AddAction(new MouseButtonAction(PiTypeAction::MouseLeft));
    TheInputMgr->AddAction(new MouseButtonAction(PiTypeAction::MouseMiddle));
    TheInputMgr->AddAction(new MouseButtonAction(PiTypeAction::MouseRight));
    TheInputMgr->AddAction(new MouseButtonAction(PiTypeAction::MouseWheel));
}


void KeyboardAction::Begin()
{
    uint type = GetActionType();

    if (type == PiTypeAction::F1)
    {
        TheConsole->Toggle();
    }
    else if (type == PiTypeAction::Esc)
    {
        TheEngine->Quit();
    }
}

void MouseButtonAction::Begin() {

    PiTypeAction::S type = GetActionType();

    if (type == PiTypeAction::MouseLeft)
    {
        TheMouse->SetLeftPressed();
    }
    else if (type == PiTypeAction::MouseMiddle)
    {
        TheMouse->SetMiddlePressed();
    }
    else if (type == PiTypeAction::MouseRight)
    {
        TheMouse->SetRightPressed();
    }
}

void MouseButtonAction::End()
{
    PiTypeAction::S type = GetActionType();

    if (type == PiTypeAction::MouseLeft)
    {
        TheMouse->SetLeftReleased();
    }
    else if (type == PiTypeAction::MouseMiddle)
    {
        TheMouse->SetMiddleReleased();
    }
    else if (type == PiTypeAction::MouseRight)
    {
        TheMouse->SetRightReleased();
    }
}

void MouseButtonAction::Update(float value)
{
    uint type = GetActionType();

    if (type == PiTypeAction::MouseWheel)
    {
        if (value > 0)
        {
            TheCamera->TiltAngleDecrease();
        }
        else
        {
            TheCamera->TiltAngleIncrease();
        }
    }
}

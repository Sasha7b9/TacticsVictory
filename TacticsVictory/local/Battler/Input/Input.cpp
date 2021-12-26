// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Input.h"
#include "Mouse.h"
#include "GUI/Widgets/Console.h"


using namespace Pi;


void Input::Init()
{
    TheInputMgr->AddAction(new NavigationAction(PiTypeAction::Left, CameraRTS::E::MoveLeft));
    TheInputMgr->AddAction(new NavigationAction(PiTypeAction::Right, CameraRTS::E::MoveRight));
    TheInputMgr->AddAction(new NavigationAction(PiTypeAction::Forward, CameraRTS::E::MoveForward));
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
        Console::self->Toggle();
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
        Mouse::self->SetLeftPressed();
    }
    else if (type == PiTypeAction::MouseMiddle)
    {
        Mouse::self->SetMiddlePressed();
    }
    else if (type == PiTypeAction::MouseRight)
    {
        Mouse::self->SetRightPressed();
    }
}

void MouseButtonAction::End()
{
    PiTypeAction::S type = GetActionType();

    if (type == PiTypeAction::MouseLeft)
    {
        Mouse::self->SetLeftReleased();
    }
    else if (type == PiTypeAction::MouseMiddle)
    {
        Mouse::self->SetMiddleReleased();
    }
    else if (type == PiTypeAction::MouseRight)
    {
        Mouse::self->SetRightReleased();
    }
}

void MouseButtonAction::Update(float value)
{
    uint type = GetActionType();

    if (type == PiTypeAction::MouseWheel)
    {
        if (value > 0)
        {
            CameraRTS::self->TiltAngleDecrease();
        }
        else
        {
            CameraRTS::self->TiltAngleIncrease();
        }
    }
}

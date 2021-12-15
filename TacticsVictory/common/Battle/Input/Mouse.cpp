// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Input/Mouse.h"
#include "GUI/Widgets/Button.h"
#include "GUI/Widgets/CursorGUI.h"
#include "Objects/GameObject.h"
#include "Scene/World/GameWorld.h"


using namespace Pi;


namespace Pi
{
    Mouse *Mouse::self = nullptr;
}


MouseObservable::~MouseObservable()
{
}

void Mouse::AddObserver(Observer<TButton, MouseObservable> *observer)
{
    observable.AddObserver(observer);
}

void Mouse::AddObserver(Observer<PanelMap, MouseObservable> *observer)
{
    observable.AddObserver(observer);
}


void Mouse::SetLeftPressed()
{
    leftNowPressed = true;
    leftIsPressed = true;
    leftNowReleased = false;

    GameObjectProperty *prop = GameObjectProperty::GetFromScreen(CursorGUI::self->position);

    if (prop)
    {
        prop->MouseEvent(1U);
    }
    else
    {
        observable.PostEvent((int)Event::LeftChanged);
    }
}


void Mouse::SetLeftReleased()
{
    bool prevLeftReleased = leftNowReleased;
    leftNowReleased = true;
    leftNowPressed = false;
    leftIsPressed = false;
    if (!prevLeftReleased)
    {
        observable.PostEvent((int)Event::LeftChanged);
    }
}

// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "Mouse.h"
#include "GUI/Widgets/Button.h"
#include "GUI/Widgets/CursorGUI.h"
#include "Scene/Objects/GameObject.h"
#include "Scene/World/GameWorld.h"


using namespace Pi;


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

    GameObjectProperty *prop = GameWorld::Get()->GameObjectPropertyInPosition(TheCursor->position);

    if (prop && prop->IsSelectable())
    {
        if (prop->IsSelected()) { prop->RemoveSelection(); }
        else                    { prop->SetSelection();    }
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

// 2021/12/13 15:33:07 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Selector/Selector.h"
#include "Input/Mouse.h"


using namespace Pi;


namespace Pi
{
    namespace PiTypeController
    {
        const S Selector = "Selector";
    }
}


Selector::Selector() : Node()
{
    SetController(new SelectorController());
}


SelectorController::SelectorController() : Controller(PiTypeController::Selector)
{
}


void SelectorController::Move()
{
    if (captured)
    {
        UpdateCaptured();
    }
    else
    {
        UpdateUnCaptured();
    }
}


void SelectorController::UpdateCaptured()
{
    if (!Mouse::self->LeftIsPressed())
    {
        captured = false;
    }
}


void SelectorController::UpdateUnCaptured()
{
    if (Mouse::self->LeftIsPressed())
    {
        captured = true;
    }
}

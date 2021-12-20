// 2021/12/20 13:34:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/GameObject_.h"


using namespace Pi;


void GameObjectController::Move()
{

}


GameObjectProperty::GameObjectProperty(GameObject &_gameObject) :
    Property(PiTypeProperty::GameObject),
    gameObject(_gameObject)
{
}


GameObjectProperty::~GameObjectProperty()
{
}


void GameObjectProperty::SetSelection()
{
    selected = true;
}


void GameObjectProperty::RemoveSelection()
{
    selected = false;
}


GameObjectProperty *GameObjectProperty::GetFromScreen(const Point2D &coord)
{
    return nullptr;
}


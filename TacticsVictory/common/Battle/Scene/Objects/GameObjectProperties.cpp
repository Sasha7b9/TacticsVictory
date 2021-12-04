// 2021/12/2 22:09:21 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/GameObjectProperties.h"


using namespace Pi;


GameObjectProperty::GameObjectProperty(GameObject *_gameObject) :
    Property(PiTypeProperty::GameObject),
    gameObject(_gameObject),
    indicator(new Indicator())
{
}


GameObjectProperty::~GameObjectProperty()
{
    delete indicator;
}


void GameObjectProperty::SetSelection()
{
    selection = true;
    TheInterfaceMgr->AddWidget(indicator);
}


void GameObjectProperty::RemoveSelection()
{
    selection = false;
    TheInterfaceMgr->RemoveWidget(indicator);
}

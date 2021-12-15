// 2021/12/1 10:05:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Unit.h"
#include "Scene/Objects/Units/PathFinder/PathFinder.h"
#include "Scene/Objects/Units/PathFinder/PathMapping.h"
#include "Scene/Objects/Units/Selector/Selector.h"


using namespace Pi;


void UnitObject::Construct()
{
    PathMapping::Construct();
}


void UnitObject::Destruct()
{
    PathMapping::Destruct();
}


UnitController::UnitController(PiTypeController::S contrType) :
    GameObjectController(PiTypeGameObject::Unit, contrType)
{
}

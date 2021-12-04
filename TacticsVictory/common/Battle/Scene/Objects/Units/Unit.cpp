// 2021/12/1 10:05:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Unit.h"


using namespace Pi;


UnitController::UnitController(Type unitType, PiTypeController::S contrType) :
    GameObjectController(GameObjectController::Type::Unit, contrType)
{
}

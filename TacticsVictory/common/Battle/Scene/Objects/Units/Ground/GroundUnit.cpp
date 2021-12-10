// 2021/12/1 10:05:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Ground/GroundUnit.h"


using namespace Pi;

GroundUnitController::GroundUnitController(const PiTypeController::S &contrType) :
    UnitController(UnitController::Type::Ground, contrType.Value())
{

}

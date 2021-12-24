// 2021/12/1 10:05:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Ground/GroundUnit_.h"


using namespace Pi;


GroundUnitObject::GroundUnitObject(TypeGroundUnit type, int id, GroundUnitController *controller) :
    UnitObject(TypeUnit::Ground, id, controller),
    typeGroundUnit(type)
{
}



GroundUnitController::GroundUnitController(GroundUnitObject *groundUnit, const UnitParameters &parameters) :
    UnitController(groundUnit, parameters)
{
}

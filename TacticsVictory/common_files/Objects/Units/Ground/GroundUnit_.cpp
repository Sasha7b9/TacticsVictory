// 2021/12/1 10:05:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Ground/GroundUnit_.h"


using namespace Pi;


Map<GroundUnitObject> GroundUnitObject::objects;


GroundUnitObject::GroundUnitObject(TypeGroundUnit type, int id, GroundUnitController *controller) :
    UnitObject(TypeUnit::Ground, id, controller),
    typeGroundUnit(type)
{
    objects.Insert(this);
}



GroundUnitController::GroundUnitController(GroundUnitObject *groundUnit) :
    UnitController(groundUnit)
{
}

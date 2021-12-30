// 2021/12/1 10:05:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Ground/GroundUnit_.h"


using namespace Pi;


Map<GroundUnitObject> GroundUnitObject::objects;


GroundUnitObject::GroundUnitObject(TypeGroundUnit type, const GameObjectParameters *params, int id) :
    UnitObject(TypeUnit::Ground, params, id),
    typeGroundUnit(type)
{
    objects.Insert(this);
}

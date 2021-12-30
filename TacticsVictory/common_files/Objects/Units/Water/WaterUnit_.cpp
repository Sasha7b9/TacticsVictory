// 2021/12/15 19:08:10 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Water/WaterUnit_.h"


using namespace Pi;


Map<WaterUnitObject> WaterUnitObject::objects;


WaterUnitObject::WaterUnitObject(TypeWaterUnit type, const GameObjectParameters *param, int id) :
    UnitObject(TypeUnit::Water, param, id),
    typeWaterUnit(type)
{
    objects.Insert(this);
}

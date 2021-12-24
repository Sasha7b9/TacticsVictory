// 2021/12/15 18:07:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Air/AirUnit_.h"


using namespace Pi;


AirUnitObject::AirUnitObject(TypeAirUnit type, int id, AirUnitController *controller) :
    UnitObject(TypeUnit::Air, id, controller),
    typeAirUnit(type)
{
}



AirUnitController::AirUnitController(AirUnitObject *object, const UnitParameters &param) :
    UnitController(object, param)
{
}

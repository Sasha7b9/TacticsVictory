// 2021/12/15 19:08:10 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Water/WaterUnit_.h"


using namespace Pi;


WaterUnitObject::WaterUnitObject(TypeWaterUnit type, int id, WaterUnitController *controller) :
    UnitObject(TypeUnit::Water, id, controller),
    typeWaterUnit(type)
{

}


WaterUnitController::WaterUnitController(WaterUnitObject *object, const UnitParameters &param) :
    UnitController(object, param)
{
}

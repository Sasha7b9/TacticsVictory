// 2021/12/15 21:41:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Water/Boat_.h"
#include "Objects/GameObjectParameters_.h"


using namespace Pi;


GameObject *Boat::Create()
{
    return nullptr;
}


Boat::Boat(int id) : WaterUnitObject(TypeWaterUnit::Boat, &parameters, id)
{
}

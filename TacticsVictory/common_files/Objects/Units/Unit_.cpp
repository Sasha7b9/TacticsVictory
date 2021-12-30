// 2021/12/1 10:05:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Unit_.h"
#include "Objects/Units/Logic/PathFinder/PathFinder.h"
#include "Objects/Units/Logic/PathFinder/PathMapping.h"
#include "Objects/Units/Logic/Selector.h"
#include "Objects/Units/Water/WaterUnit_.h"
#include "Objects/Units/Air/AirUnit_.h"
#include "Objects/PoolObjects_.h"
#include "Objects/Staff/Commander_.h"


using namespace Pi;


Map<UnitObject> UnitObject::objects;


void UnitObject::Move(float dT)
{
    if (params == nullptr)
    {
        return;
    }

    GameObject::Move(dT);

    commander->Update(dT);

    driver->Update(dT);
}

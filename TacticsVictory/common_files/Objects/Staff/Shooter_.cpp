// 2021/12/17 0:05:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Staff/Shooter_.h"
#include "Objects/Units/Unit_.h"
#include "Objects/Units/Air/AirUnit_.h"
#include "Objects/Units/Air/Airplane_.h"
#include "Objects/Units/Air/Helicopter_.h"
#include "Objects/Units/Ground/GroundUnit_.h"
#include "Objects/Units/Ground/Robot_.h"
#include "Objects/Units/Ground/Tank_.h"
#include "Objects/Units/Ground/Worm.h"
#include "Objects/Units/Water/WaterUnit_.h"
#include "Objects/Units/Water/Boat_.h"
#include "Objects/Units/Water/Submarine_.h"


using namespace Pi;


Shooter::Shooter(GameObject *_object) : object(_object)
{

}


Shooter *Shooter::New(GameObject *object)
{
    if(object->typeGameObject == TypeGameObject::Unit)
    {
        UnitObject *unit = object->GetUnitObject();

        if (unit->typeUnit == TypeUnit::Air)
        {
            TypeAirUnit type = unit->GetAirUnit()->typeAirUnit;
    
            if (type == TypeAirUnit::Airplane)        return new Shooter(object);
            else if (type == TypeAirUnit::Helicopter) return new Shooter(object);
        }
        else if (unit->typeUnit == TypeUnit::Ground)
        {
            TypeGroundUnit type = unit->GetGroundUnit()->typeGroundUnit;
    
            if (type == TypeGroundUnit::Robot)     return new Shooter(object);
            else if (type == TypeGroundUnit::Tank) return new Shooter(object);
            else if (type == TypeGroundUnit::Worm) return new Shooter(object);
        }
        else if (unit->typeUnit == TypeUnit::Water)
        {
            TypeWaterUnit type = unit->GetWaterUnit()->typeWaterUnit;
    
            if (type == TypeWaterUnit::Boat)           return new Shooter(object);
            else if (type == TypeWaterUnit::Submarine) return new Shooter(object);
        }
    }

    return nullptr;
}


void Shooter::Update(float dT)
{

}

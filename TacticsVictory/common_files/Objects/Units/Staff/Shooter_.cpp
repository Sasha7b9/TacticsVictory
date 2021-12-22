﻿// 2021/12/17 0:05:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Staff/Shooter_.h"
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


Shooter::Shooter(UnitController *_controller) : controller(_controller)
{

}


Shooter *Shooter::New(UnitController *controller)
{
    if (controller->BelongAir())
    {
        TypeAirUnit::S type = ((AirUnitController *)controller)->GetAirUnitObject()->typeAirUnit;

        if (type == TypeAirUnit::Airplane)        return new ShooterAirplane(controller);
        else if (type == TypeAirUnit::Helicopter) return new ShooterHelicopter(controller);
    }
    else if (controller->BelongGround())
    {
        TypeGroundUnit::S type = ((GroundUnitController *)controller)->GetGroundUnitObject()->typeGroundUnit;

        if (type == TypeGroundUnit::Robot)     return new ShooterRobot(controller);
        else if (type == TypeGroundUnit::Tank) return new ShooterTank(controller);
        else if (type == TypeGroundUnit::Worm) return new ShooterWorm(controller);
    }
    else if (controller->BelongWater())
    {
        TypeWaterUnit::S type = ((WaterUnitController *)controller)->GetWaterUnitObject()->typeWaterUnit;

        if (type == TypeWaterUnit::Boat)           return new ShooterBoat(controller);
        else if (type == TypeWaterUnit::Submarine) return new ShooterSubmarine(controller);
    }

    return nullptr;
}


void Shooter::Update(float dT)
{

}
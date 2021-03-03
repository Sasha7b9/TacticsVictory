// 2021/02/25 21:40:14 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Scene/Objects/Units/Ground/Tank/TankC.h"
#include "Scene/Objects/Units/UnitObjectC.h"


GameObjectSpecific *TankSpecific::Create(Tank *tank)
{
    return new TankSpecificC(tank);
}


void TankSpecificC::Update(float timeStep)
{
    UnitObjectSpecificC::Update(timeStep);
}

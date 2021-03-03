// 2021/02/25 22:10:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Game/Messages/GameMessages_.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Scene/Objects/Units/Ground/Tank/TankS.h"
#include "Scene/Objects/Units/UnitObjectS.h"


GameObjectSpecific *TankSpecific::Create(Tank *tank)
{
    return new TankSpecificS(tank);
}


void TankSpecificS::Update(float timeStep)
{
    UnitObjectSpecificS::Update(timeStep);
}

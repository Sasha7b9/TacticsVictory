// 2021/02/25 22:10:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Game/Messages/GameMessages_.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Scene/Objects/Units/Ground/Tank/TankS.h"
#include "Scene/Objects/Units/UnitObjectS.h"


void Tank::RegisterObject()
{
    TheContext->RegisterFactory<Tank>();
}


void Tank::Update(float timeStep)
{
    UnitObject::Update(timeStep);
}


void TankSpecificS::Update(float /*timeStep*/)
{

}

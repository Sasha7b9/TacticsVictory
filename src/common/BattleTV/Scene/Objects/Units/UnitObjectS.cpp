// 2021/02/26 17:28:47 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Accessories/Accessories_.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Scene/Objects/Units/UnitObjectS.h"


UnitObjectSpecific *UnitObjectSpecific::Create(UnitObject *object)
{
    return new UnitObjectSpecificS(object);
}


void UnitObjectSpecificS::Update(float timeStep)
{
    UnitObjectSpecific::Update(timeStep);
}

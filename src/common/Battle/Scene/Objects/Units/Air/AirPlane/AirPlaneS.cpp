// 2021/03/10 15:34:58 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Air/AirPlane/AirPlane_.h"
#include "Scene/Objects/Units/Air/AirPlane/AirPlaneS.h"


void AirPlane::CreateSpecific()
{
    specific = new AirPlaneSpecificS(this);
}


void AirPlaneSpecificS::Update(float dT)
{
    UnitSpecificS::Update(dT);
}

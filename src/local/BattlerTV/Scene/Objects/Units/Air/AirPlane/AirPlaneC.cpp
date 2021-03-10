// 2021/03/10 15:31:48 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Air/AirPlane/AirPlaneC.h"



void AirPlane::CreateSpecific()
{
    specific = new AirPlaneSpecificC(this);
}


void AirPlaneSpecificC::Update(float dT)
{
    UnitSpecificC::Update(dT);
}

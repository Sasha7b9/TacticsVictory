// 2021/02/23 11:36:18 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Ammo/AirBomb_.h"


static const MinPP minAirBomb{ 0.0f };
static const MaxPP maxAirBomb{ 1.0f, 120.0f, 10.0f };


AirBomb::AirBomb(Context *context) :
    AmmoObject(context, minAirBomb, maxAirBomb)
{

}

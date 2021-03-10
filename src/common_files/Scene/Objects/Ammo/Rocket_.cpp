// 2021/02/23 11:05:07 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Ammo/Rocket_.h"


static const MinPP minRocket = { 0.0f };
static const MaxPP maxRocket(1.0f, 120.0f, 10.0f);


Rocket::Rocket(Context *context) : AmmoObject(context, minRocket, maxRocket)
{

}

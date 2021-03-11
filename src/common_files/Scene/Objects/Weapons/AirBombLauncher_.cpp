// 2021/02/23 11:28:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Weapons/AirBombLauncher_.h"


static const MinPP minAirBombLauncher{ 0.0f };
static const MaxPP maxAirBombLauncher{ 1.0f, 120.0f, 10.0f };


AirBombLauncher::AirBombLauncher(Context *context) :
    WeaponObject(context, minAirBombLauncher, maxAirBombLauncher)
{

}

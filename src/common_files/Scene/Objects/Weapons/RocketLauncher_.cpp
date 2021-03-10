// 2021/02/22 21:16:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Weapons/RocketLauncher_.h"


static const MinPP minRocketLauncher = { 0.0f };
static const MaxPP maxRocketLauncher = { 1.0f, 120.0f, 10.0f };


RocketLauncher::RocketLauncher(Context *context) :
    WeaponObject(context, minRocketLauncher, maxRocketLauncher)
{

}

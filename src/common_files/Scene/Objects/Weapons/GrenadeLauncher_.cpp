// 2021/02/22 21:30:00 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Weapons/GrenadeLauncher_.h"


static const MinPP minGrenadeLauncher = { 0.0f };
static const MaxPP maxGrenadeLauncher(1.0f, 120.0f, 10.0f);


GrenadeLauncher::GrenadeLauncher(Context *context) :
    WeaponObject(context, minGrenadeLauncher, maxGrenadeLauncher)
{

}

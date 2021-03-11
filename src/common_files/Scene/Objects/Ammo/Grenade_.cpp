// 2021/02/23 10:58:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Ammo/Grenade_.h"


static const MinPP minGrenade{ 0.0f };
static const MaxPP maxGrenade{ 1.0f, 120.0f, 10.0f };


Grenade::Grenade(Context *context) : AmmoObject(context, minGrenade, maxGrenade)
{

}

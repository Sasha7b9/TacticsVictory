/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Scene/Objects/_GameObject.h"


class AmmoObject : public GameObject
{
public:
    AmmoObject(Context *context = TheContext);
};


#include "Scene/Objects/Ammo/_AirBomb.h"
#include "Scene/Objects/Ammo/_Grenade.h"
#include "Scene/Objects/Ammo/_Mine.h"
#include "Scene/Objects/Ammo/_Rocket.h"
#include "Scene/Objects/Ammo/_RollingBomb.h"


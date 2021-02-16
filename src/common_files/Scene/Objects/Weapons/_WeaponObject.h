// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/_GameObject.h"


class WeaponObject : public GameObject
{
public:
    WeaponObject(Context *context = TheContext);
};


#include "Scene/Objects/Weapons/_GrenadeLauncher.h"
#include "Scene/Objects/Weapons/_Gun.h"
#include "Scene/Objects/Weapons/_Laser.h"
#include "Scene/Objects/Weapons/_MachineGun.h"
#include "Scene/Objects/Weapons/_RocketLauncher.h"

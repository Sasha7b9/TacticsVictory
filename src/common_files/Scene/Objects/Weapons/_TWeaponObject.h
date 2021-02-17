// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/_TGameObject.h"


class WeaponObject : public GameObject
{
public:
    WeaponObject(Context *context = TheContext);
};


#include "Scene/Objects/Weapons/_TGrenadeLauncher.h"
#include "Scene/Objects/Weapons/_TGun.h"
#include "Scene/Objects/Weapons/_TLaser.h"
#include "Scene/Objects/Weapons/_TMachineGun.h"
#include "Scene/Objects/Weapons/_TRocketLauncher.h"

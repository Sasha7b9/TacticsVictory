/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Scene/Objects/_TGameObject.h"


class AmmoObject : public GameObject
{
public:
    AmmoObject(Context *context = TheContext);
};


#include "Scene/Objects/Ammo/_TAirBomb.h"
#include "Scene/Objects/Ammo/_TGrenade.h"
#include "Scene/Objects/Ammo/_TMine.h"
#include "Scene/Objects/Ammo/_TRocket.h"
#include "Scene/Objects/Ammo/_TRollingBomb.h"


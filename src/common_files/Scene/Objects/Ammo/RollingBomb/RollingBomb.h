/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Scene/Objects/Ammo/_AmmoObject.h"



class RollingBomb : public AmmoObject
{
public:
    RollingBomb(Context *context = TheContext);

private:
    DEFAULT_MEMBERS(RollingBomb);
};

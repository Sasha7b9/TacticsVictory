/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Game/Objects/Ammo/AmmoObject.h"



class RollingBomb : public AmmoObject
{
public:
    RollingBomb(Context *context = gContext);

private:
    DEFAULT_MEMBERS(RollingBomb);
};

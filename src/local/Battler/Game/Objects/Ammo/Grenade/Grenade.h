#pragma once
#include "Game/Objects/Ammo/AmmoObject.h"



class Grenade : public AmmoObject
{
public:
    Grenade(Context *context = gContext);

private:
    DEFAULT_MEMBERS(Grenade);
};

#pragma once
#include "Game/Objects/Weapons/WeaponObject.h"



class Laser : public WeaponObject
{
public:
    Laser(Context *context = gContext);

private:
    DEFAULT_MEMBERS(Laser);
};

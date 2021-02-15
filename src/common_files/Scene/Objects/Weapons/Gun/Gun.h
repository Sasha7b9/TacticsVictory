#pragma once
#include "Scene/Objects/Weapons/WeaponObject.h"



class Gun : public WeaponObject
{
public:
    Gun(Context *context = TheContext);

private:
    DEFAULT_MEMBERS(Gun);
};

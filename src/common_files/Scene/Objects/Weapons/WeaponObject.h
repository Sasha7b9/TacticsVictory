#pragma once
#include "Scene/Objects/_GameObject.h"



class WeaponObject : public GameObject
{
public:
    WeaponObject(Context *context = TheContext);

private:
    DEFAULT_MEMBERS(WeaponObject);
};

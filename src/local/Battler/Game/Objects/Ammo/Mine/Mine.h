#pragma once
#include "Game/Objects/Ammo/AmmoObject.h"



class Mine : public AmmoObject
{
public:
    Mine(Context *context = gContext);

private:
    DEFAULT_MEMBERS(Mine);
};

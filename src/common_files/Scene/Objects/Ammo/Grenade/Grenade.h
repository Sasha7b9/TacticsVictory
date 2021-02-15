/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Game/Objects/Ammo/AmmoObject.h"



class Grenade : public AmmoObject
{
public:
    Grenade(Context *context = TheContext);

private:
    DEFAULT_MEMBERS(Grenade);
};

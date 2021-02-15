/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Game/Objects/Ammo/AmmoObject.h"



class AirBomb : public AmmoObject
{
public:
    AirBomb(Context *context = TheContext);

private:
    DEFAULT_MEMBERS(AirBomb);
};

/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Game/Objects/Ammo/AmmoObject.h"



class Mine : public AmmoObject
{
public:
    Mine(Context *context = TheContext);

private:
    DEFAULT_MEMBERS(Mine);
};

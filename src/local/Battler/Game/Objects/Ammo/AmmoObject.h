/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Game/Objects/GameObject.h"



class AmmoObject : public GameObject
{
public:
    AmmoObject(Context *context = TheContext);

private:
    DEFAULT_MEMBERS(AmmoObject);
};

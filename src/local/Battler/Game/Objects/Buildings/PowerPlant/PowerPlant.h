/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Game/Objects/Buildings/BuildingObject.h"



class PowerPlant : public BuildingObject
{
public:
    PowerPlant(Context *context = TheContext);

private:
    DEFAULT_MEMBERS(PowerPlant);
};

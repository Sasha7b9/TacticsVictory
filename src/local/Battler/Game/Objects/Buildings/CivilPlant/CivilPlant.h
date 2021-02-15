/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Game/Objects/Buildings/BuildingObject.h"



class CivilPlant : public BuildingObject
{
public:
    CivilPlant(Context *context = gContext);

private:
    DEFAULT_MEMBERS(CivilPlant);
};

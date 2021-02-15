/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Game/Objects/Buildings/BuildingObject.h"



class WarehouseAmmo : public BuildingObject
{
public:
    WarehouseAmmo(Context *context = TheContext);

private:
    DEFAULT_MEMBERS(WarehouseAmmo);
};

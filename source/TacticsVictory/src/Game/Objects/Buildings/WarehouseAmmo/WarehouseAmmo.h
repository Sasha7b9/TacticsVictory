#pragma once


#include "Game/Objects/Buildings/BuildingObject.h"


class WarehouseAmmo : public BuildingObject
{
public:
    WarehouseAmmo(Context *context = gContext);

private:
    WarehouseAmmo& operator=(const WarehouseAmmo&)
    {};
};
#pragma once
#include "Game/Objects/Buildings/BuildingObject.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PowerPlant : public BuildingObject
{
public:
    PowerPlant(Context *context = gContext);

private:
    PowerPlant& operator=(const PowerPlant&)
    {};
};

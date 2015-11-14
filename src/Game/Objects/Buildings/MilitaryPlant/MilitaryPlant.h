#pragma once


#include "Game/Objects/Buildings/BuildingObject.h"


class MilitaryPlant : public BuildingObject
{
public:
    MilitaryPlant(Context *context = gContext);

private:
    MilitaryPlant& operator=(const MilitaryPlant&)
    {};
};
#pragma once
#include "Game/Objects/Buildings/BuildingObject.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CivilPlant : public BuildingObject
{
public:
    CivilPlant(Context *context = gContext);

private:
    CivilPlant& operator=(const CivilPlant&)
    {};
};

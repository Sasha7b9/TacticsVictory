#pragma once


#include "Game/Objects/Buildings/BuildingObject.h"


class ProcessingPlant : public BuildingObject
{
public:
    ProcessingPlant(Context *context = gContext);

private:
    ProcessingPlant& operator=(const ProcessingPlant&)
    {};
};
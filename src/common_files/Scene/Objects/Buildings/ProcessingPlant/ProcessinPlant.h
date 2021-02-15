/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Game/Objects/Buildings/BuildingObject.h"



class ProcessingPlant : public BuildingObject
{
public:
    ProcessingPlant(Context *context = TheContext);

private:
    DEFAULT_MEMBERS(ProcessingPlant);
};

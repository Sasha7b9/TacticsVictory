/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Game/Objects/Buildings/BuildingObject.h"



class Shaft : public BuildingObject
{
public:
    Shaft(Context *context = gContext);

private:
    DEFAULT_MEMBERS(Shaft);
};

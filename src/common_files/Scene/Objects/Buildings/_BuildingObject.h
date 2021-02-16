// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/_GameObject.h"


class BuildingObject : public GameObject
{
public:
    BuildingObject(Context *context = TheContext);
};


#include "Scene/Objects/Buildings/_CivilPlant.h"
#include "Scene/Objects/Buildings/_MilitaryPlant.h"
#include "Scene/Objects/Buildings/_PowerPlant.h"
#include "Scene/Objects/Buildings/_ProcessinPlant.h"
#include "Scene/Objects/Buildings/_Shaft.h"
#include "Scene/Objects/Buildings/_WarehouseAmmo.h"

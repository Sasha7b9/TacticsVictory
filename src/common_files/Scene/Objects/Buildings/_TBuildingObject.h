// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/_TGameObject.h"


class BuildingObject : public GameObject
{
public:
    BuildingObject(Context *context = TheContext);
};


#include "Scene/Objects/Buildings/_TCivilPlant.h"
#include "Scene/Objects/Buildings/_TMilitaryPlant.h"
#include "Scene/Objects/Buildings/_TPowerPlant.h"
#include "Scene/Objects/Buildings/_TProcessinPlant.h"
#include "Scene/Objects/Buildings/_TShaft.h"
#include "Scene/Objects/Buildings/_TWarehouseAmmo.h"

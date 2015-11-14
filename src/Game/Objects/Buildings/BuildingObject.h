#pragma once


#include "Game/Objects/GameObject.h"


class BuildingObject : public GameObject
{
public:
    BuildingObject(Context *context = gContext);

private:
    BuildingObject& operator=(const BuildingObject&)
    {};
};
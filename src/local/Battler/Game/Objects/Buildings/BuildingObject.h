#pragma once
#include "Game/Objects/GameObject.h"



class BuildingObject : public GameObject
{
public:
    BuildingObject(Context *context = TheContext);

private:
    DEFAULT_MEMBERS(BuildingObject);
};

#pragma once


#include "Game/Objects/GameObject.h"


class UnitObject : public GameObject
{
public:
    UnitObject(Context *context = gContext);

private:
    UnitObject& operator=(const UnitObject&)
    {};
};

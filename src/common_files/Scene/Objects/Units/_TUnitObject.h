#pragma once
#include "Scene/Objects/_TGameObject.h"


class UnitObject : public GameObject
{
public:

    static Vector<UnitObject *> storage;

private:

    UnitObject();
};

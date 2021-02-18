#include "stdafx.h"
#include "Scene/Objects/Units/_TUnitObject.h"


Vector<UnitObject *> UnitObject::storage;


UnitObject::UnitObject() : GameObject()
{
    storage.Push(this);
}

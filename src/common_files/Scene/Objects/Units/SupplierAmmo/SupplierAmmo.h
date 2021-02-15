#pragma once
#include "Game/Objects/Units/UnitObject.h"



class SupplierAmmo : public UnitObject
{
public:
    SupplierAmmo(Context *context = TheContext);

private:
    DEFAULT_MEMBERS(SupplierAmmo);
};

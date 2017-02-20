#pragma once


#include "Game/Objects/Units/UnitObject.h"


class SupplierAmmo : public UnitObject
{
public:
    SupplierAmmo(Context *context = gContext);

private:
    SupplierAmmo& operator=(const SupplierAmmo&)
    {};
};
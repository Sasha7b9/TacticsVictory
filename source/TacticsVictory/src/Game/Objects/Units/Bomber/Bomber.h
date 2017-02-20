#pragma once


#include "Game/Objects/Units/UnitObject.h"


class Bomber : public UnitObject
{
public:
    Bomber(Context *context = gContext);

private:
    Bomber& operator=(const Bomber&)
    {};
};
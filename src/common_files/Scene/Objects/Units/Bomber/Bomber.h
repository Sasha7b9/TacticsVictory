#pragma once
#include "Game/Objects/Units/UnitObject.h"



class Bomber : public UnitObject
{
public:
    Bomber(Context *context = TheContext);

private:
    DEFAULT_MEMBERS(Bomber);
};

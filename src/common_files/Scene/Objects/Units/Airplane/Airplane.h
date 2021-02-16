#pragma once
#include "Scene/Objects/Units/UnitObject.h"



class Airplane : public UnitObject
{
public:
    Airplane(Context *context = TheContext);

private:
    DEFAULT_MEMBERS(Airplane);
};

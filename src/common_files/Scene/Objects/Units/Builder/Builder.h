#pragma once
#include "Game/Objects/Units/UnitObject.h"



class Builder : public UnitObject
{
public:
    Builder(Context *context = TheContext);

private:
    DEFAULT_MEMBERS(Builder);
};

#pragma once


#include "Game/Objects/Units/UnitObject.h"


class Builder : public UnitObject
{
public:
    Builder(Context *context = gContext);

private:
    Builder& operator=(const Builder&)
    {};
};
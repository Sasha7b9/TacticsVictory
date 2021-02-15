#pragma once
#include "Game/Objects/Units/UnitObject.h"



class Robot : public UnitObject
{
public:
    Robot(Context *context = gContext);

private:
    DEFAULT_MEMBERS(Robot);
};

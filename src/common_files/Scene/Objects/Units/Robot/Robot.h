#pragma once
#include "Scene/Objects/Units/UnitObject.h"



class Robot : public UnitObject
{
public:
    Robot(Context *context = TheContext);

private:
    DEFAULT_MEMBERS(Robot);
};

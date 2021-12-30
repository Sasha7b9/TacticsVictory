// 2021/12/15 21:25:58 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Ground/Robot_.h"
#include "Objects/GameObjectParameters_.h"


using namespace Pi;


GameObject *Robot::Create()
{
    return nullptr;
}


Robot::Robot(int id) : GroundUnitObject(TypeGroundUnit::Robot, &parameters, id)
{
}

// 2021/12/15 21:32:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Ground/Worm.h"
#include "Objects/GameObjectParameters_.h"


using namespace Pi;


GameObject *Worm::Create()
{
    return nullptr;
}


Worm::Worm(int id) : GroundUnitObject(TypeGroundUnit::Worm, &parameters, id)
{
}

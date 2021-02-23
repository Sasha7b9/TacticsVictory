// 2021/02/23 11:39:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Ammo/TCAirBomb.h"


CAirBomb::CAirBomb() : AirBomb()
{

}


SharedPtr<CAirBomb> CAirBomb::Create()
{
    SharedPtr<CAirBomb> bomb(new CAirBomb());

    return bomb;
}

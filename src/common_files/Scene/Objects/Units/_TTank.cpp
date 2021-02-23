// 2021/02/22 15:40:37 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#include "stdafx.h"
#include "Scene/Objects/Units/_TTank.h"


Tank::Tank() : UnitObject()
{

}


SharedPtr<Tank> Tank::Create()
{
    SharedPtr<Tank> tank(new Tank());

    return tank;
}

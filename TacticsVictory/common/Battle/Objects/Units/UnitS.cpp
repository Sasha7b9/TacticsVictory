// 2021/12/20 14:30:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Unit_.h"


using namespace Pi;


void UnitObject::Construct()
{
}


void UnitObject::Destruct()
{
}


UnitObject::UnitObject(TypeUnit type, int id) : GameObject(TypeGameObject::Unit, id), typeUnit(type)
{
}

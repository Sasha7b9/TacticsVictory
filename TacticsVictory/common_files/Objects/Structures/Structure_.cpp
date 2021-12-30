// 2021/12/15 19:32:54 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Structures/Structure_.h"


using namespace Pi;


StructureObject::StructureObject(TypeStructure type, const GameObjectParameters *params, int id) :
    GameObject(TypeGameObject::Structure, params, id),
    typeStructure(type)
{
}

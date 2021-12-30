// 2021/12/20 14:27:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Unit_.h"
#include "Graphics/Geometry/PoolGeometry.h"
#include "Objects/Units/Logic/PathFinder/PathMapping.h"


using namespace Pi;


void UnitObject::Construct()
{
    PathMapping::Construct();
}


void UnitObject::Destruct()
{
    PathMapping::Destruct();
}


UnitObject::UnitObject(TypeUnit type, const GameObjectParameters *params, int id) :
    GameObject(TypeGameObject::Unit, params, id),
    typeUnit(type)
{
    GetNodeGeometry()->AppendNewSubnode(PoolGeometry::Get(TTypeGeometry::GizmoObject));
    objects.Insert(this);
}

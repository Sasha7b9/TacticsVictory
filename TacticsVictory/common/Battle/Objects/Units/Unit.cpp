// 2021/12/1 10:05:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Unit.h"
#include "Objects/Units/PathFinder/PathFinder.h"
#include "Objects/Units/PathFinder/PathMapping.h"
#include "Objects/Units/Selector/Selector.h"
#include "Graphics/Geometry/PoolGeometry.h"


using namespace Pi;


void UnitObject::Construct()
{
    PathMapping::Construct();
}


void UnitObject::Destruct()
{
    PathMapping::Destruct();
}


UnitObject::UnitObject(TTypeUnit::S type) : GameObject(TTypeGameObject::Unit), typeUnit(type)
{
    AppendNewSubnode(PoolGeometry::Get(TTypeGeometry::GizmoObject));
}


UnitController::UnitController(PiTypeController::S type) : GameObjectController(TTypeGameObject::Unit, type)
{

}

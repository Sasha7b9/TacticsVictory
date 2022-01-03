// 2021/12/1 10:05:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Unit_.h"
#include "Objects/Units/Logic/PathFinder/PathFinder_.h"
#include "Objects/Units/Logic/PathFinder/PathMapping_.h"
#include "Objects/Units/Logic/Selector_.h"
#include "Objects/Units/Water/WaterUnit_.h"
#include "Objects/Units/Air/AirUnit_.h"
#include "Objects/PoolObjects_.h"
#include "Objects/Staff/Commander_.h"

#ifdef PiCLIENT
    #include "Graphics/Geometry/PoolGeometry.h"
    #include "Objects/Units/Logic/PathFinder/PathMapping_.h"
#endif


using namespace Pi;


Map<UnitObject> UnitObject::objects;


void UnitObject::Construct()
{
#ifdef PiCLIENT

    PathMapping::Construct();

#endif
}


void UnitObject::Destruct()
{
#ifdef PiCLIENT

    PathMapping::Destruct();

#endif
}


UnitObject::UnitObject(TypeUnit type, const GameObjectParameters *params, int id) :
    GameObject(TypeGameObject::Unit, params, id),
    typeUnit(type)
{
#ifdef PiCLIENT

    GetNodeGeometry()->AppendNewSubnode(PoolGeometry::Get(TTypeGeometry::GizmoObject));

#endif

    objects.Insert(this);
}


void UnitObject::Move(float dT)
{
    GameObject::Move(dT);

    commander->Update(dT);

    driver->Update(dT);
}

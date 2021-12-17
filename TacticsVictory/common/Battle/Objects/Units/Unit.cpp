// 2021/12/1 10:05:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Unit.h"
#include "Objects/Units/PathFinder/PathFinder.h"
#include "Objects/Units/PathFinder/PathMapping.h"
#include "Objects/Units/Selector/Selector.h"
#include "Graphics/Geometry/PoolGeometry.h"
#include "Objects/Units/Water/WaterUnit.h"


using namespace Pi;


void UnitObject::Construct()
{
    PathMapping::Construct();
}


void UnitObject::Destruct()
{
    PathMapping::Destruct();
}


UnitObject::UnitObject(TypeUnit type) : GameObject(TypeGameObject::Unit), typeUnit(type)
{
    AppendNewSubnode(PoolGeometry::Get(TTypeGeometry::GizmoObject));
}


UnitController::UnitController(PiTypeController::S type, const UnitParameters *_param) :
    GameObjectController(TypeGameObject::Unit, type)
{
    param = _param->Replicate();
}


UnitController::~UnitController()
{
    delete commander;
    delete driver;
    delete shooter;
    delete param;
}


UnitController *UnitController::AppendTask(const UnitTask *task)
{
    commander->AppendTask(task);

    return this;
}


void UnitController::Preprocess()
{
    GameObjectController::Preprocess();
    
    commander = Commander::New(this);
    driver = Driver::New(this);
    shooter = Shooter::New(this);

    commander->SetDriver(driver);
}


void UnitController::Move()
{
    GameObjectController::Move();

    float dT = TheTimeMgr->GetFloatDeltaTime();

    commander->Update(dT);

    driver->Update(dT);

    shooter->Update(dT);
}


bool UnitController::CanExecute(UnitTask::Type task) const
{
    if (task == UnitTask::Type::Move)
    {
        return true;
    }
    else if (task == UnitTask::Type::Dive)
    {
        WaterUnitObject *unit = GetWaterUnitOject();

        if (unit)
        {
            if (unit->typeWaterUnit == TypeWaterUnit::Submarine)
            {
                return true;
            }
        }
    }
    else if (task == UnitTask::Type::Rotate)
    {
        return true;
    }

    return false;
}

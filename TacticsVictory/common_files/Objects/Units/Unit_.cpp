// 2021/12/1 10:05:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Unit_.h"
#include "Objects/Units/Logic/PathFinder/PathFinder.h"
#include "Objects/Units/Logic/PathFinder/PathMapping.h"
#include "Objects/Units/Logic/Selector.h"
#include "Objects/Units/Water/WaterUnit_.h"


using namespace Pi;


Map<UnitObject> UnitObject::objects;


UnitController::UnitController(UnitObject *_object, const UnitParameters &_param) :
    GameObjectController(_object),
    param(_param),
    object(_object)
{
}


UnitController::~UnitController()
{
    delete commander;
    delete driver;
    delete shooter;
}


UnitController *UnitController::AppendTask(const CommanderTask *task)
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


void UnitController::Move(float dT)
{
    GameObjectController::Move(dT);

    commander->Update(dT);

    driver->Update(dT);

    shooter->Update(dT);
}


bool UnitController::CanExecute(CommanderTask::Type task) const
{
    if (task == CommanderTask::Type::Move)
    {
        return true;
    }
    else if (task == CommanderTask::Type::Dive)
    {
        WaterUnitObject *unit = GetWaterUnitObject();

        if (unit)
        {
            if (unit->typeWaterUnit == TypeWaterUnit::Submarine)
            {
                return true;
            }
        }
    }
    else if (task == CommanderTask::Type::Rotate)
    {
        return true;
    }

    return false;
}

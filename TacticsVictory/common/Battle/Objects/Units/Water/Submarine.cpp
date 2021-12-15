// 2021/12/15 22:10:02 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Water/Submarine.h"


using namespace Pi;


GameObject *Submarine::Create()
{
    return nullptr;
}


SubmarineController::SubmarineController() : WaterUnitController(TTypeWaterUnit::Submarine)
{

}


SubmarineController::SubmarineController(const SubmarineController &controller) : WaterUnitController(controller)
{

}


SubmarineController::~SubmarineController()
{

}


Controller *SubmarineController::Replicate() const
{
    return new SubmarineController(*this);
}


void SubmarineController::Preprocess()
{
    WaterUnitController::Preprocess();
}

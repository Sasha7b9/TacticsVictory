// 2021/12/15 19:35:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Structures/ArmoryPlant.h"


using namespace Pi;


GameObject *ArmoryPlant::Create()
{
    return nullptr;
}


ArmoryPlantController::ArmoryPlantController() : StructureController(TypeStructure::ArmoryPlant)
{

}


ArmoryPlantController::ArmoryPlantController(const ArmoryPlantController &controller) :
    StructureController(controller)
{

}


ArmoryPlantController::~ArmoryPlantController()
{

}


Controller *ArmoryPlantController::Replicate() const
{
    return new ArmoryPlantController(*this);
}


void ArmoryPlantController::Preprocess()
{
    StructureController::Preprocess();
}

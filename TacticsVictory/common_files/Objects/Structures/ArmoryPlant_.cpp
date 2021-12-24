// 2021/12/15 19:35:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Structures/ArmoryPlant_.h"


using namespace Pi;


ArmoryPlant *ArmoryPlant::Create()
{
    return nullptr;
}


ArmoryPlant::ArmoryPlant(int id) : StructureObject(TypeStructure::ArmoryPlant, id, new ArmoryPlantController(this))
{
}


ArmoryPlantController::ArmoryPlantController(ArmoryPlant *plant) : StructureController(plant)
{
}


ArmoryPlantController::~ArmoryPlantController()
{
}


void ArmoryPlantController::Preprocess()
{
    StructureController::Preprocess();
}

// 2021/12/15 19:36:54 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Structures/CivilianPlant_.h"


using namespace Pi;


GameObject *CivilianPlant::Create()
{
    return nullptr;
}


CivilianPlantController::CivilianPlantController() : StructureController(TypeStructure::CivilianPlant)
{

}


CivilianPlantController::CivilianPlantController(const CivilianPlantController &controller) :
    StructureController(controller)
{

}


CivilianPlantController::~CivilianPlantController()
{

}


Controller *CivilianPlantController::Replicate() const
{
    return new CivilianPlantController(*this);
}


void CivilianPlantController::Preprocess()
{
    StructureController::Preprocess();
}
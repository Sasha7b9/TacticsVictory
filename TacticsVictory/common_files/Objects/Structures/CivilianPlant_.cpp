// 2021/12/15 19:36:54 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Structures/CivilianPlant_.h"


using namespace Pi;


GameObject *CivilianPlant::Create()
{
    return nullptr;
}


CivilianPlant::CivilianPlant(int id) :
    StructureObject(TypeStructure::CivilianPlant, id, new CivilianPlantController(this))
{
}



CivilianPlantController::CivilianPlantController(CivilianPlant *plant) : StructureController(plant)
{

}


CivilianPlantController::~CivilianPlantController()
{

}


void CivilianPlantController::Preprocess()
{
    StructureController::Preprocess();
}
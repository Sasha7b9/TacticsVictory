// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "MilitaryPlant.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MilitaryPlant::MilitaryPlant(Context *context) :
    BuildingObject(context)
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MilitaryPlant::RegisterObject(Context *context)
{
    context->RegisterFactory<MilitaryPlant>();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
SharedPtr<MilitaryPlant> MilitaryPlant::Create()
{
    SharedPtr<Node> node(gScene->CreateChild());
    SharedPtr<MilitaryPlant> plant(node->CreateComponent<MilitaryPlant>());
    plant->Init();
    return plant;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MilitaryPlant::Init()
{
    LoadFromFile();
    Normalize(2.0f);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MilitaryPlant::LoadFromFile()
{
    char *fileName = "Models\\Buildings\\MilitaryPlant\\MilitaryPlant.mdl";
    char *materialsName = "Models\\Buildings\\MilitaryPlant\\MilitaryPlant.txt";

    modelObject = node_->CreateComponent<StaticModel>();
    modelObject->SetViewMask(VIEW_MASK_FOR_MISSILE);
    modelObject->SetModel(gCache->GetResource<Model>(fileName));
    modelObject->ApplyMaterialList(materialsName);
    modelObject->SetCastShadows(true);
}

/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"
#ifdef CLIENT
#include "Scene/TCScene.h"
#endif
#include "Scene/_TScene.h"
#include "Scene/Objects/Buildings/_TMilitaryPlant.h"


MilitaryPlant::MilitaryPlant(Context *context) :
    BuildingObject(context)
{
    physics->Init(this);
}


void MilitaryPlant::RegisterObject(Context *context)
{
    context->RegisterFactory<MilitaryPlant>();
}


SharedPtr<MilitaryPlant> MilitaryPlant::Create(uint row, uint col)
{
    SharedPtr<Node> node(TheScene->scene->CreateChild());
    SharedPtr<MilitaryPlant> plant(node->CreateComponent<MilitaryPlant>());
    plant->Init();
    plant->SetCoord({ row, col });
    return plant;
}


void MilitaryPlant::Init()
{
    LoadFromFile();
    Normalize(2.0f);
}


void MilitaryPlant::LoadFromFile()
{
    char *fileName = "Models\\Buildings\\MilitaryPlant\\MilitaryPlant.mdl";
    char *materialsName = "Models\\Buildings\\MilitaryPlant\\MilitaryPlant.txt";

    modelObject = node_->CreateComponent<StaticModel>();
    modelObject->SetViewMask(VIEW_MASK_FOR_MISSILE);
    modelObject->SetModel(TheCache->GetResource<Model>(fileName));
    modelObject->ApplyMaterialList(materialsName);
    modelObject->SetCastShadows(true);
}

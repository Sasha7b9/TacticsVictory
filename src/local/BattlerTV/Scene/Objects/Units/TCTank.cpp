// 2021/02/22 15:40:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#include "stdafx.h"
#include "Scene/TCScene.h"
#include "Scene/Objects/Units/TCTank.h"


Vector<CTank *> CTank::storage;


CTank::CTank(Context *context) : Tank(context)
{

}


void CTank::RegisterObject()
{
    TheContext->RegisterFactory<CTank>();
}


SharedPtr<CTank> CTank::Create(uint row, uint col)
{
    SharedPtr<Node> node(TheScene->scene->CreateChild("CTank", LOCAL));
    SharedPtr<CTank> tank(node->CreateComponent<CTank>(LOCAL));
    tank->node = node;

    tank->LoadFromFile();

    node->SetPosition({ (float)row, 0, -(float)col });

    storage.Push(tank);

    return tank;
}


void CTank::LoadFromFile()
{
    JSONFile *file(TheCache->GetResource<JSONFile>("Models/Tank.json"));

    JSONValue &root = file->GetRoot();
    JSONValue modelValue = root.Get("model");

    String fileModel = modelValue.Get("fileModel").GetString();
    String fileMaterials = modelValue.Get("fileMaterials").GetString();

    modelObject = node->CreateComponent<StaticModel>();
    modelObject->SetViewMask(VIEW_MASK_FOR_MISSILE);
    modelObject->SetModel(TheCache->GetResource<Model>(fileModel));
    modelObject->ApplyMaterialList(fileMaterials);
    modelObject->SetCastShadows(true);

    speed = root.Get("speed").GetFloat();

    deltaRotate = root.Get("deltaRotate").GetFloat();

    Quaternion rotate(deltaRotate, Vector3::UP);
    node->SetRotation(Quaternion(0, Vector3::UP));
    node->Rotate(rotate);
}


void CTank::FixedUpdate(float /*time*/)
{

}

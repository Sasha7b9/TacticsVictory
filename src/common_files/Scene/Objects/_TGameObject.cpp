// 2021/02/18 22:31:17 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/_TGameObject.h"


Vector<GameObject *> GameObject::storage;


GameObject::GameObject(Context *context) : LogicComponent(context)
{
    storage.Push(this);
}


void GameObject::LoadFromJSON(const String &fileName)
{
    JSONFile *file(TheCache->GetResource<JSONFile>(fileName));

    JSONValue &root = file->GetRoot();
    JSONValue modelValue = root.Get("model");

    String fileModel = modelValue.Get("fileModel").GetString();
    String fileMaterials = modelValue.Get("fileMaterials").GetString();

    modelObject = node_->CreateComponent<StaticModel>();
    modelObject->SetViewMask(VIEW_MASK_FOR_MISSILE);
    modelObject->SetModel(TheCache->GetResource<Model>(fileModel));
    modelObject->ApplyMaterialList(fileMaterials);
    modelObject->SetCastShadows(true);

    speed = root.Get("speed").GetFloat();

    deltaRotate = root.Get("deltaRotate").GetFloat();

    Quaternion rotate(deltaRotate, Vector3::UP);
    node_->SetRotation(Quaternion(0, Vector3::UP));
    node_->Rotate(rotate);
}

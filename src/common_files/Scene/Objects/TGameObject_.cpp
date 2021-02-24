// 2021/02/18 22:31:17 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Core/TMath_.h"
#include "Scene/Objects/TGameObject_.h"


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

    staticModel = node_->CreateComponent<StaticModel>();
    staticModel->SetViewMask(VIEW_MASK_FOR_MISSILE);
    staticModel->SetModel(TheCache->GetResource<Model>(fileModel));
    staticModel->ApplyMaterialList(fileMaterials);
    staticModel->SetCastShadows(true);

    speed = root.Get("speed").GetFloat();

    shiftRotate = root.Get("deltaRotate").GetFloat();

    Quaternion rotate(shiftRotate, Vector3::UP);
    node_->SetRotation(Quaternion(0, Vector3::UP));
    node_->Rotate(rotate);
}


void GameObject::Normalize(float k)
{
    Vector3 pos = GetPosition();
    node_->SetPosition(Vector3::ZERO);
    node_->SetScale(1.0f);

    BoundingBox box = staticModel->GetModel()->GetBoundingBox();

    Vector3 delta = box.max_ - box.min_;

    float divider = Math::Max(delta.x_, delta.y_, delta.z_);

    Vector3 scale = Vector3::ONE * k / divider;

    shiftPosition.y_ = -box.min_.y_ * k / divider;
    shiftPosition.z_ = -(box.max_.z_ + box.min_.z_) * k / 2.0f / divider;
    shiftPosition.x_ = (box.max_.x_ + box.min_.x_) * k / 2.0f / divider;

    node_->SetScale(scale);

    SetPosition(pos);
}


Vector3 GameObject::GetPosition() const
{
    return node_->GetPosition() - shiftPosition;
}


void GameObject::SetPosition(const Vector3 &position)
{
    node_->SetPosition(position + shiftPosition);
}

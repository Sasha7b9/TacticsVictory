// 2021/02/18 22:31:17 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Core/Math_.h"
#include "Scene/Objects/GameObject_.h"
#include "Scene/Objects/Units/UnitObject_.h"


Vector<GameObject *> GameObject::storage;


void ShiftParameters::RegisterObject()
{
    TheContext->RegisterFactory<ShiftParameters>();
}


GameObject::GameObject(Context *context) : LogicComponent(context)
{
    storage.Push(this);
}


void GameObject::RegisterObject()
{
    UnitObject::RegisterObject();
    ShiftParameters::RegisterObject();
}


void GameObject::OnNodeSet(Node *node)
{
    if (node)
    {
        node->CreateComponent<ShiftParameters>();
    }

    LogicComponent::OnNodeSet(node);
}


void GameObject::LoadFromJSON(const String &fileName)
{
    ShiftParameters *shift = node_->GetComponent<ShiftParameters>();

    JSONFile *file(TheCache->GetResource<JSONFile>(fileName));

    JSONValue &root = file->GetRoot();
    JSONValue modelValue = root.Get("model");

    String fileModel = modelValue.Get("fileModel").GetString();
    String fileMaterials = modelValue.Get("fileMaterials").GetString();

    staticModel = node_->CreateComponent<StaticModel>(LOCAL);
    staticModel->SetViewMask(VIEW_MASK_FOR_MISSILE);
    staticModel->SetModel(TheCache->GetResource<Model>(fileModel));
    staticModel->ApplyMaterialList(fileMaterials);
    staticModel->SetCastShadows(true);

//    speed = root.Get("speed").GetFloat();

    shift->rotate = root.Get("deltaRotate").GetFloat();

    Quaternion rotate(shift->rotate, Vector3::UP);
    node_->SetRotation(Quaternion(0, Vector3::UP));
    node_->Rotate(rotate);
}


void GameObject::Normalize(float k)
{
    ShiftParameters *shift = node_->GetComponent<ShiftParameters>();

    Vector3 pos = GetPosition();
    node_->SetPosition(Vector3::ZERO);
    node_->SetScale(1.0f);

    BoundingBox box = staticModel->GetModel()->GetBoundingBox();

    Vector3 delta = box.max_ - box.min_;

    float divider = Math::Max(delta.x_, delta.y_, delta.z_);

    Vector3 scale = Vector3::ONE * k / divider;

    shift->position.y_ = -box.min_.y_ * k / divider;
    shift->position.z_ = -(box.max_.z_ + box.min_.z_) * k / 2.0f / divider;
    shift->position.x_ = (box.max_.x_ + box.min_.x_) * k / 2.0f / divider;

    node_->SetScale(scale);

    SetPosition(pos);
}


Vector3 GameObject::GetPosition() const
{
    return node_->GetPosition() - node_->GetComponent<ShiftParameters>()->position;
}


void GameObject::SetPosition(const Vector3 &position)
{
    node_->SetPosition(position + node_->GetComponent<ShiftParameters>()->position);
}


void GameObject::Update(float timeStep)
{
    LogicComponent::Update(timeStep);
}

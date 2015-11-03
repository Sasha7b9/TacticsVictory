#include <stdafx.h>


#include "Tank.h"
#include "Core/Math.h"


HashMap<lTank::Key, lTank::TankStruct> lTank::parameters;


lTank::lTank(Context *context) : LogicComponent(context)
{
    if (parameters.Empty())
    {
        parameters[Small] = TankStruct(Small, "Models/Tank.json");
        parameters[T_34_76] = TankStruct(T_34_76, "Models/T-34-76-2.json");
    }
}

void lTank::RegisterObject(Context* context)
{
    context->RegisterFactory<lTank>();
}

void lTank::Init(Type type_)
{
    type = type_;
    LoadFromFile();
    Normalize();
}

void lTank::LoadFromFile()
{
    char *fileName = parameters[type].fileName;
    JSONFile *file = gCache->GetResource<JSONFile>(fileName);

    JSONValue modelValue = file->GetRoot().Get("model");

    String fileModel = modelValue.Get("fileModel").GetString();
    String fileMaterials = modelValue.Get("fileMaterials").GetString();

    modelObject = node_->CreateComponent<StaticModel>();
    modelObject->SetModel(gCache->GetResource<Model>(fileModel));
    modelObject->ApplyMaterialList(fileMaterials);
    modelObject->SetCastShadows(true);
}

void lTank::Normalize()
{
    Vector3 pos = node_->GetPosition();
    node_->SetPosition({0.0f, 0.0f, 0.0f});
    node_->SetScale(1.0f);

    BoundingBox box = modelObject->GetModel()->GetBoundingBox();

    Vector3 delta = box.max_ - box.min_;

    float divider = Math::Max(delta.x_, delta.y_, delta.z_);

    float k = 1.0f;
    Vector3 scale = {k / divider, k / divider, k / divider};

    deltaPos.y_ = -box.min_.y_ / divider * k;
    deltaPos.z_ = -(box.max_.z_ + box.min_.z_) / 2.0f / divider * k - 0.5f;
    deltaPos.x_ = (box.max_.x_ + box.min_.x_) / 2.0f / divider * k + 0.5f;

    node_->SetScale(scale);

    SetPosition(pos);
}

void lTank::SetPosition(const Vector3& pos)
{
    node_->SetPosition(pos + deltaPos);
}

Vector3 lTank::GetPosition()
{
    return node_->GetPosition() - deltaPos;
}

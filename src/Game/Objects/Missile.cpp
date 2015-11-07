#include <stdafx.h>


#include "Missile.h"
#include "Core/Math.h"


Missile::Missile(Context *context)
    : GameObject(context)
{

}

void Missile::RegisterObject(Context *context)
{
    context->RegisterFactory<Missile>();
}

void Missile::Update(float timeStep)
{

}

void Missile::Init()
{
    LoadFromFile();
    Normalize();
}

SharedPtr<Missile> Missile::Create(const Vector3 &speedShooter, const Vector3 &position, Tank *target)
{
    SharedPtr<Node> node(gScene->CreateChild("Missile"));
    SharedPtr<Missile> missile(node->CreateComponent<Missile>());
    missile->Init();
    missile->node_->SetPosition(position + Vector3(0.0f, 3.0f, 0.0f));
    return missile;
}

void Missile::LoadFromFile()
{
    model = node_->CreateComponent<StaticModel>();
    model->SetModel(gCache->GetResource<Model>("Models/Missile.mdl"));
    model->ApplyMaterialList("Models/Missile.txt");
    model->SetCastShadows(true);
}

void Missile::Normalize()
{
    node_->SetPosition({0.0f, 0.0f, 0.0f});
    node_->SetScale(1.0f);

    BoundingBox box = model->GetModel()->GetBoundingBox();

    Vector3 delta = box.max_ - box.min_;

    float divider = Math::Max(delta.x_, delta.y_, delta.z_);

    float k = 1.0f;
    Vector3 scale = {k / divider, k / divider, k / divider};

    deltaPos.y_ = -box.min_.y_ / divider * k;
    deltaPos.z_ = -(box.max_.z_ + box.min_.z_) / 2.0f / divider * k;
    deltaPos.x_ = (box.max_.x_ + box.min_.x_) / 2.0f / divider * k;

    node_->SetScale(scale);
}



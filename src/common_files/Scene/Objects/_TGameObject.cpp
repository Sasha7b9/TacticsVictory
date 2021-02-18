// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Core/_TMath.h"
#ifdef CLIENT
#include "GUI/TCursor.h"
#include "GUI/GuiGame/TContextMenuUnit.h"
#endif
#include "Scene/Objects/_TGameObject.h"
#include "Scene/Objects/Units/Logic/_TTranslator.h"


static uint creatorID = 0;


GameObject::GameObject(Context *context) : LogicComponent(context)
{
    selector = new SelectorComponentGameObject();

    physics = new PhysicsComponentGameObject();

    graphics = new GraphicsComponentGameObject();

    common = new CommonComponentGameObject();

    common->id = ++creatorID;
}


GameObject::~GameObject()
{
    delete reloader;
    delete selector;
    delete physics;
    delete graphics;
    delete gui;
    delete common;
}


char *GameObject::CommonComponentGameObject::GetName()
{
    return name;
}


Vector3 PhysicsComponentGameObject::GetPosition()
{
    return keeper->node_->GetPosition() - deltaPos;
}


void PhysicsComponentGameObject::SetPosition(const Vector3& pos)
{
    keeper->node_->SetPosition(pos + keeper->physics->deltaPos);
}


void GraphicsComponentGameObject::Normalize(float k)
{
    Vector3 pos = keeper->physics->GetPosition();
    keeper->node_->SetPosition({0.0f, 0.0f, 0.0f});
    keeper->node_->SetScale(1.0f);

    BoundingBox box = keeper->graphics->modelObject->GetModel()->GetBoundingBox();

    Vector3 delta = box.max_ - box.min_;

    float divider = Math::Max(delta.x_, delta.y_, delta.z_);

    Vector3 scale = {k / divider, k / divider, k / divider};

    keeper->physics->deltaPos.y_ = -box.min_.y_ / divider * k;
    keeper->physics->deltaPos.z_ = -(box.max_.z_ + box.min_.z_) / 2.0f / divider * k;
    keeper->physics->deltaPos.x_ = (box.max_.x_ + box.min_.x_) / 2.0f / divider * k;

    keeper->node_->SetScale(scale);

    keeper->physics->SetPosition(pos);
}


void PhysicsComponentGameObject::SetCoord(const Coord& coord)
{
    SetPosition(coord.ToVector3());
}

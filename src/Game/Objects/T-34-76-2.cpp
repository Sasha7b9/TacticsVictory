#include <stdafx.h>


#include "T-34-76-2.h"
#include "Core/Math.h"


lT34_76_2::lT34_76_2() : lMovingObject()
{
    Load();
}

void lT34_76_2::Load()
{
    JSONFile *file = gCache->GetResource<JSONFile>("Models/T-34-76-2.json");

    JSONValue modelValue = file->GetRoot().Get("model");
    JSONValue fileNameValue = modelValue.Get("name");
    String fileName = fileNameValue.GetString();

    modelNode = gScene->CreateChild("Tank");
    modelObject = modelNode->CreateComponent<StaticModel>();
    modelObject->SetModel(gCache->GetResource<Model>(fileName));
    modelObject->SetCastShadows(true);

    Normalize();
}

void lT34_76_2::Normalize()
{
    Vector3 pos = modelNode->GetPosition();
    modelNode->SetPosition({0.0f, 0.0f, 0.0f});
    modelNode->SetScale(1.0f);

    BoundingBox box = modelObject->GetModel()->GetBoundingBox();

    Vector3 delta = box.max_ - box.min_;

    float divider = Math::Max(delta.x_, delta.y_, delta.z_);

    float k = 0.75f;
    Vector3 scale = {k / divider, k / divider, k / divider};

    deltaPos.y_ = -box.min_.y_ / divider * k;
    deltaPos.z_ = -(box.max_.z_ + box.min_.z_) / 2.0f / divider * k - 0.5f;
    deltaPos.x_ = (box.max_.x_ + box.min_.x_) / 2.0f / divider * k + 0.5f;

    modelNode->SetScale(scale);

    SetPosition(pos);
}

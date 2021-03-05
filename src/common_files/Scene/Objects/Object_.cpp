// 2021/02/18 22:31:17 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Core/Math_.h"
#include "Scene/Objects/Object_.h"
#include "Scene/Objects/Units/Unit_.h"


Vector<ObjectT *> ObjectT::storage;


ObjectSpecific::ObjectSpecific(ObjectT *_object) : Object(TheContext),
    object(_object)
{
}



ObjectT::ObjectT(Context *context) : LogicComponent(context)
{
    shift = new ShiftParameters();

    physics = new PhysicsParameters(this);

    storage.Push(this);
}


void ObjectT::OnNodeSet(Node *node)
{
    LogicComponent::OnNodeSet(node);

    if (node)
    {
        node->SetVar(VAR_OBJECT_TYPE_NAME, GetTypeName());
    }
}


void ObjectT::Start()
{
    LogicComponent::Start();
}


void ObjectT::DelayedStart()
{
    LogicComponent::DelayedStart();

    CreateSpecific();
}


void ObjectT::LoadFromJSON(const String &fileName)
{
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


void ObjectT::Normalize(float k)
{
    Vector3 pos = physics->position.Get();
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

    physics->position.Set(pos);
}


Vector3 PositionPP::Get() const
{
    return object->GetObjectNode()->GetPosition() /*- object->shift->position*/;
}


void PositionPP::Set(const Vector3 &position)
{
    object->GetObjectNode()->SetPosition(position /* + object->shift->position*/);
}


Vector3 DirectionPP::Get() const
{
    return { -1.0f, 0.0f, 0.0f };
}


void ObjectT::Update(float timeStep)
{
    LogicComponent::Update(timeStep);

    specific->Update(timeStep);
}


void ObjectT::Compress(VectorBuffer &buffer, bool /*log*/)
{
    uint id = node_->GetID();
    Vector3 position = node_->GetPosition();

    buffer.WriteUInt(id);
    buffer.WriteVector3(position);
}


void ObjectT::Decompress(MemoryBuffer &buffer, bool /*log*/)
{
    Vector3 position = buffer.ReadVector3();

    node_->SetPosition(position);
}


int ObjectT::NestingDepth()
{
    int result = 0;

    Node *node = node_;

    while (node != nullptr)
    {
        node = node->GetParent();
        result++;
    }

    return result;
}

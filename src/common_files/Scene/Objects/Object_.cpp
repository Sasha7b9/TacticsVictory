// 2021/02/18 22:31:17 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Core/Math_.h"
#include "Scene/Objects/Object_.h"


Vector<ObjectT *> ObjectT::storage;

ObjectT *ObjectT::empty = nullptr;


ObjectSpecific::ObjectSpecific(ObjectT *_object) : Object(TheContext),
    object(_object)
{
}



ObjectT::ObjectT(Context *context, const MinPP &min, const MaxPP &max) : LogicComponent(context)
{
    shift = new ShiftParameters();

    storage.Push(this);

    physics = new PhysicsParameters(this, min, max);
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

    CreateSpecific();
}


void ObjectT::DelayedStart()
{
    LogicComponent::DelayedStart();
}


bool ObjectT::LoadFromJSON(pchar name)
{
    JSONFile *file(TheCache->GetResource<JSONFile>(name));

    if (file == nullptr)
    {
        LOGERRORF("Don't load file %s", name);
        TheEngine->Exit();

        return false;
    }

    JSONValue &root = file->GetRoot();
    JSONValue modelValue = root.Get("model");

    String fileModel = modelValue.Get("fileModel").GetString();
    String fileMaterials = modelValue.Get("fileMaterials").GetString();

    staticModel = node_->CreateComponent<StaticModel>(LOCAL);
    staticModel->SetViewMask(VIEW_MASK_FOR_MISSILE);
    staticModel->SetModel(TheCache->GetResource<Model>(fileModel));
    staticModel->ApplyMaterialList(fileMaterials);
    staticModel->SetCastShadows(true);

    shift->rotateY = root.Get("deltaRotateY").GetFloat();

    physics->rot.SetWorld(Quaternion(-90.0f, Vector3::UP));

    Quaternion rotation = physics->rot.GetWorld();

    return true;
}


void ObjectT::Normalize(float k)
{
    Vector3 pos = physics->pos.GetWorld();
    node_->SetPosition(Vector3::ZERO);
    node_->SetScale(1.0f);

    BoundingBox box = staticModel->GetModel()->GetBoundingBox();

    Vector3 delta = box.max_ - box.min_;

    float divider = Math::Max(delta.x_, delta.y_, delta.z_);

    Vector3 scale = Vector3::ONE * k / divider;

//    shift->position.y_ = -box.min_.y_ * k / divider;
//    shift->position.z_ = -(box.max_.z_ + box.min_.z_) * k / 2.0f / divider;
//    shift->position.x_ = (box.max_.x_ + box.min_.x_) * k / 2.0f / divider;

    node_->SetScale(scale);

    physics->pos.SetWorld(pos);
}


void ObjectT::Update(float timeStep)
{
    LogicComponent::Update(timeStep);

    specific->Update(timeStep);
}


void ObjectT::Compress(VectorBuffer &buffer)
{
    uint id = node_->GetID();
    Vector3 position = node_->GetPosition();
    Quaternion rotation = node_->GetRotation();

    buffer.WriteUInt(id);
    buffer.WriteVector3(position);
    buffer.WriteQuaternion(rotation);
}


void ObjectT::Decompress(MemoryBuffer &buffer)
{
    Vector3 position = buffer.ReadVector3();
    Quaternion rotation = buffer.ReadQuaternion();

    node_->SetPosition(position);
    node_->SetRotation(rotation);
}


void ObjectT::OnPostRenderUpdate()
{
    specific->OnPostRenderUpdate();
}


int ObjectT::NestingDepth() const
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


void ObjectT::StoreState()
{
    state.WriteVector3(physics->pos.GetWorld());
}


void ObjectT::RestoreState()
{
    physics->pos.SetWorld(state.ReadVector3());
}


bool ObjectT::IsIntersectionWithUnitOrBuilding() const
{
    BoundingBox box = GetBoundingBox();

    for (ObjectT *object : storage)
    {
        if ((object->IsUnit() || object->IsBuilding()) && object != this)
        {
            BoundingBox another = object->GetBoundingBox();

            if (box.IsInside(another))
            {
                return true;
            }
        }
    }

    return false;
}


BoundingBox ObjectT::GetBoundingBox() const
{
    return staticModel->GetBoundingBox();
}

#include <stdafx.h>


#include "Missile.h"
#include "Core/Math.h"
#include "Game/Objects/Units/Tank/Tank.h"


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
    /*
    HiresTimer timer;

    static int prevElapsedTime = 0;

    static long long time;
    */

    typedef void(Missile::* FuncUpdate)(float);
    static FuncUpdate funcs[] =
    {
        &Missile::UpdateBegin,
        &Missile::UpdateEscortTarget
    };

    if(node_)
    {
        FuncUpdate func = funcs[state];
        (this->*func)(timeStep);
        /*
        time += timer.GetUSec(false);

        if((int)gTime->GetElapsedTime() != prevElapsedTime)
        {
            prevElapsedTime = (int)gTime->GetElapsedTime();
            LOGINFOF("update missiles %f", (float)time / 1e6f);
            time = 0;
        }
        */
    }
}

void Missile::Init(const Vector3 &speedShooter, const Vector3 &position, Tank *target)
{
    LoadFromFile();
    Normalize();

    this->target = target;
    this->position = position;
    speed = speedShooter;
    absSpeed = speedShooter.Length() * 1.01f;
    speed.y_ = absSpeed;
}

SharedPtr<Missile> Missile::Create(const Vector3 &speedShooter, const Vector3 &position, Tank *target)
{
    SharedPtr<Node> node(gScene->CreateChild("Missile"));
    SharedPtr<Missile> missile(node->CreateComponent<Missile>());
    missile->Init(speedShooter, position, target);
    missile->node_->SetPosition(position + Vector3(0.0f, 3.0f, 0.0f));
    return missile;
}

void Missile::LoadFromFile()
{
    model = node_->CreateComponent<StaticModel>();
    model->SetModel(gCache->GetResource<Model>("Models/Missile.mdl"));
    model->ApplyMaterialList("Models/Missile.txt");
    //model->SetCastShadows(true);
}

void Missile::Normalize()
{
    node_->SetPosition({0.0f, 0.0f, 0.0f});
    node_->SetScale(1.0f);

    BoundingBox box = model->GetModel()->GetBoundingBox();

    Vector3 delta = box.max_ - box.min_;

    float divider = Math::Max(delta.x_, delta.y_, delta.z_);

    float k = 0.25f;
    Vector3 scale = {k / divider, k / divider, k / divider};

    deltaPos.y_ = -box.min_.y_ / divider * k;
    deltaPos.z_ = -(box.max_.z_ + box.min_.z_) / 2.0f / divider * k;
    deltaPos.x_ = (box.max_.x_ + box.min_.x_) / 2.0f / divider * k;

    node_->SetScale(scale);
}

void Missile::UpdateBegin(float dT)
{
    position += speed * dT;
    node_->SetPosition(position);

    time += dT;
    distance += absSpeed * dT;

    if(position.y_ > heightBeginExcortTarget)
    {
        state = EscortTarget;
    }
}

void Missile::UpdateEscortTarget(float dT)
{
    time += dT;

    const float deltaAiming = 0.1f;             // From this time need aim to target
    static float timeElapsedAiming = 0.0f;      // Time elapsed form last aiming

    if(timeElapsedAiming == 0.0f)
    {
        AimToTarget();
    }

    position += speed * dT;
    node_->SetPosition(position);

    time += dT;
    distance += absSpeed * dT;

    timeElapsedAiming += dT;

    if(timeElapsedAiming > deltaAiming)
    {
        timeElapsedAiming = 0.0f;
    }

    if(time > rangeTime || distance > rangeDistance || (position - target->GetPosition()).Length() < 0.3f)
    {
        gScene->NodeRemoved(node_);
    }
}

void Missile::AimToTarget()
{
    Vector3 posTarget = target->GetPosition() + Vector3(0.0f, 0.25f, 0.0f);

    speed = posTarget - position;
    speed.Normalize();
    speed *= absSpeed;

    Quaternion rotate(Vector3::DOWN, position - posTarget);

    float yaw = rotate.YawAngle();
    float pitch = rotate.PitchAngle();
    float roll = rotate.RollAngle();

    node_->SetRotation(rotate);
}

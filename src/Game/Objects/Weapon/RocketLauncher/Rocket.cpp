#include <stdafx.h>


#include "Rocket.h"
#include "Core/Math.h"
#include "Game/Objects/Units/Tank/Tank.h"
#include "Game/Objects/Weapon/AmmoEvents.h"
#include "Core/Camera.h"
#include "Game/Sounds.h"
#include "Game/Particles.h"


static PODVector<Rocket*> rockets;
Mutex Rocket::mutexVectorRockets;


Rocket::Rocket(Context *context)
    : GameObject(context)
{
    if (rockets.Size() == 0)
    {
//        SubscribeToEvent(Urho3D::E_POSTRENDERUPDATE, URHO3D_HANDLER(Rocket, HandlePostRenderUpdate));
    }
}

void Rocket::RegisterObject(Context *context)
{
    context->RegisterFactory<Rocket>();
}

void Rocket::Init(const Vector3 &speedShooter, const Vector3 &position, Tank *target)
{
    if (!model)
    {
        LoadFromFile();
        Normalize();
        CreateSmoke();
    }

    this->target = target;
    this->position = position;
    absSpeed = speedShooter.Length() * 1.5f;
    speed = Vector3(0.0f, absSpeed, 0.0f);
    state = Begin;

    rotate = Quaternion(Vector3::UP, Vector3::UP);
}

SharedPtr<Rocket> Rocket::Create(const Vector3 &speedShooter, const Vector3 &position, Tank *target)
{
    SharedPtr<Rocket> rocket;

    Rocket::mutexVectorRockets.Acquire();

    uint size = rockets.Size();
    for(uint i = 0; i < size; i++)
    {
        Rocket *rock = rockets[i];
        if(!rock->node_->IsEnabled())
        {
            rocket = rock;
            rocket->Init(speedShooter, position, target);
            gScene->AddChild(rocket->node_);
            break;
        }
    }

    if (rocket == nullptr)
    {
        SharedPtr<Node> node(gScene->CreateChild("Rocket"));
        if (rockets.Size())
        {
            rocket = (Rocket*)node->CloneComponent(rockets[0]->node_->GetComponent<Rocket>());
        }
        else
        {
            rocket = node->CreateComponent<Rocket>();
        }
        rocket->Init(speedShooter, position, target);

        rockets.Push(rocket);
    }

    Rocket::mutexVectorRockets.Release();

    return rocket;
}

void Rocket::LoadFromFile()
{
    if (rockets.Size())
    {
        model = (StaticModel*)node_->CloneComponent(rockets[0]->node_->GetComponent<StaticModel>());
    }
    if (!model)
    {
        model = node_->CreateComponent<StaticModel>();
        model->SetModel(gCache->GetResource<Model>("Models/Rocket.mdl"));
        model->ApplyMaterialList("Models/Rocket.txt");
    }
}

void Rocket::Normalize()
{
    node_->SetPosition({0.0f, 0.0f, 0.0f});
    node_->SetScale(1.0f);

    BoundingBox box = model->GetModel()->GetBoundingBox();

    Vector3 delta = box.max_ - box.min_;

    float divider = Math::Max(delta.x_, delta.y_, delta.z_);

    float k = 0.4f;
    scale = {k / divider, k / divider, k / divider};

    deltaPos.y_ = -box.min_.y_ / divider * k;
    deltaPos.z_ = -(box.max_.z_ + box.min_.z_) / 2.0f / divider * k;
    deltaPos.x_ = (box.max_.x_ + box.min_.x_) / 2.0f / divider * k;

    node_->SetScale(scale);
}

void Rocket::UpdateBegin()
{
//    mutexPosition.Acquire();

    position += speed * dT;

    time += dT;
    distance += absSpeed * dT;

    if(position.y_ > heightBeginExcortTarget)
    {
        state = EscortTarget;
    }
//    mutexPosition.Release();
}

void Rocket::UpdateEscortTarget()
{
    if(firstUpdateEscort)
    {
        speed.x_ = 0.0f;
        speed.z_ = 0.0f;
        speed.y_ = absSpeed;
        firstUpdateEscort = false;
    }

    // Calculate necessary angle to target
    Vector3 dirToTarget = target->GetPosition() + Vector3(0.0f, 0.25f, 0.0f) - position;
    dirToTarget.Normalize();

    Vector3 dir = speed;
    dir.Normalize();

    float angleNeed = dir.Angle(dirToTarget);

    float angleCan = rotateSpeed * dT;

    Vector3 axisRotate = dir.CrossProduct(dirToTarget);

    if(angleCan >= angleNeed)
    {
        rotate = Quaternion(Vector3::UP, dirToTarget);

        Quaternion qutRotate(angleNeed, axisRotate);
        speed = qutRotate * speed;
    }
    else
    {
        Quaternion qutRotate(angleCan, axisRotate);
        speed = qutRotate * speed;

        rotate = Quaternion(Vector3::UP, speed);
    }

    position += speed * dT;
}

void Rocket::CreateSmoke()
{
    const uint NUM_BILLBOARDS = 50;

    Node *smokeNode = node_->CreateChild("Smoke");
    smokeNode->SetScale(1.0f);

    billboardObject = smokeNode->CreateComponent<BillboardSet>();
    billboardObject->SetNumBillboards(NUM_BILLBOARDS);
    billboardObject->SetMaterial(gCache->GetResource<Material>("Materials/LitSmoke.xml"));
    billboardObject->SetSorted(false);

    for(uint j = 0; j < NUM_BILLBOARDS; ++j)
    {
        Billboard *bb = billboardObject->GetBillboard(j);
        bb->position_ = Vector3(Random(10.0f) - 5.0f, Random(10.0f) - 5.0f, Random(10.0f) - 5.0f);
        bb->size_ = Vector2(Random(2.0f) + 3.0f, Random(2.0f) + 3.0f);
        bb->rotation_ = Random() * 360.0f;
        bb->enabled_ = true;

        billboards.Push(bb);
        rotBillboard.Push(bb->rotation_);
    }

    billboardObject->Commit();

    Node* forEmitter = node_->CreateChild("Emitter");

    if (rockets.Size())
    {
        forEmitter->CloneComponent(rockets[0]->node_->GetChild("Emitter")->GetComponent<ParticleEmitter>());
    }
    else
    {
        ParticleEmitter *emitter = forEmitter->CreateComponent<ParticleEmitter>();

        if (rockets.Size())
        {
            pe = rockets[0]->pe;
        }
        else
        {
            XMLFile xmlParticle = XMLFile(gContext);
            SharedPtr<File> file(gCache->GetFile("Particle/SnowExplosion.xml"));
            if (file)
            {
                bool res = xmlParticle.Load(*file);
                pe = new ParticleEffect(gContext);
                XMLElement root = xmlParticle.GetRoot("particleemitter");
                res = pe->Load(root);
            }
        }
        emitter->SetEffect(pe);
        emitter->SetEmitting(true);
        emitter->Commit();
    }
}

void Rocket::CalculateAnimate()
{
    const float BILLBOARD_ROTATION_SPEED = 50.0f;

    for (float &rotation : rotBillboard)
    {
        rotation += BILLBOARD_ROTATION_SPEED * dT;
    }
}

void Rocket::AnimateSmoke()
{
    uint size = billboards.Size();
    for (uint i = 0; i < size; i++)
    {
        billboards[i]->rotation_ = rotBillboard[i];
    }
    billboardObject->Commit();
}

void Rocket::UpdateOn()
{
    typedef void(Rocket::* FuncUpdate)();
    static FuncUpdate funcs[] =
    {
        &Rocket::UpdateBegin,
        &Rocket::UpdateEscortTarget
    };

    if(node_ && node_->IsEnabled())
    {
        FuncUpdate func = funcs[state];
        (this->*func)();

        CalculateAnimate();
    }
}

class ThreadRocket : public Thread
{
public:
    virtual void ThreadFunction();
    void SetParameters(uint startIndex, uint endIndex);
    bool inProcess = false;
private:
    uint start = 0;
    uint end = 0;
};


void ThreadRocket::SetParameters(uint startIndex, uint endIndex)
{
    start = startIndex;
    end = endIndex;
}

void ThreadRocket::ThreadFunction()
{
    inProcess = true;

    for (uint i = start; i <= end; i++)
    {
        Rocket *rocket = rockets[i];

        if (rocket->needCalculate)
        {
            rocket->UpdateOn();
            rocket->needCalculate = false;
        }
    }

    inProcess = false;
}

void Rocket::SetParameters(float timeStep)
{
    Rocket::mutexVectorRockets.Acquire();

    if(node_ && node_->IsEnabled())
    {
        dT = timeStep;

        node_->SetPosition(position);
        node_->SetRotation(rotate);

        AnimateSmoke();

        if (state != Begin && VerifyOnIntersectionTerrain())
        {
            Sounds::Play(Sound_Explosion, position);
            //Particles::Emitting(Particle_Explosion, position);
            node_->SetEnabled(false);
            return;
        }
        else if(time > rangeTime || distance > rangeDistance)
        {
            gScene->RemoveChild(node_);
            node_->SetEnabled(false);
            return;
        }
        else if ((position - target->GetPosition()).Length() < 0.3f)
        {
            for(uint i = 0; i < rockets.Size(); i++)
            {
                if(node_ == rockets[i]->node_)
                {
                    i = i;
                }
            }

            Sounds::Play(Sound_Explosion, position);

            VariantMap eventData = GetEventDataMap();
            eventData[AmmoEvent::P_TYPE] = Hit_Missile;
            eventData[AmmoEvent::P_OBJECT] = target;
            SendEvent(E_HIT, eventData);

            node_->SetEnabled(false);
            return;
        }

        needCalculate = true;
    }

    Rocket::mutexVectorRockets.Release();
}

void Rocket::UpdateAll(float timeStep)
{
    static ThreadRocket thread1;
    static ThreadRocket thread2;
    static ThreadRocket thread3;
    static ThreadRocket thread4;

    while(thread1.inProcess) {};
    thread1.Stop();

    while(thread2.inProcess) {};
    thread2.Stop();

    while(thread3.inProcess) {};
    thread3.Stop();

    while(thread4.inProcess) {};
    thread4.Stop();

    mutexVectorRockets.Acquire();
    uint size = rockets.Size();

    for(uint i = 0; i < size; i++)
    {
        rockets[i]->SetParameters(timeStep);
    }
    mutexVectorRockets.Release();

    uint rocketsOnThread = (size + 1) / 4;

    if (size > 0)
    {
        thread1.SetParameters(0, rocketsOnThread);
        thread1.Run();
        if (size > 1)
        {
            thread2.SetParameters(rocketsOnThread + 1, 2 * rocketsOnThread);
            thread2.Run();
            if (size > 2)
            {
                thread3.SetParameters(2 * rocketsOnThread + 1, 3 * rocketsOnThread);
                thread3.Run();
                if (size > 3)
                {
                    thread4.SetParameters(3 * rocketsOnThread + 1, size - 1);
                    thread4.Run();
                }
            }
        }
    }
}

/*
Vector3 Rocket::GetPosition()
{
    mutexPosition.Acquire();
    Vector3 ret = position;
    mutexPosition.Release();
    return ret;
}

void Rocket::SetPosition(Vector3 &pos)
{
    mutexPosition.Acquire();
    position = pos;
    mutexPosition.Release();
}
*/

bool Rocket::VerifyOnIntersectionTerrain()
{
    Vector3 direction = speed;
    direction.Normalize();
    Ray ray(position, direction);
    PODVector<RayQueryResult> results;
    RayOctreeQuery query(results, ray, Urho3D::RAY_TRIANGLE, 0.5f, Urho3D::DRAWABLE_GEOMETRY);
    gScene->GetComponent<Octree>()->Raycast(query);

    uint size = results.Size();
    if (size)
    {
        for (auto result : results)
        {
            String name = result.drawable_->GetNode()->GetName();
            if (name == NODE_TERRAIN)
            {
                return true;
            }
        }
    }
    return false;
}

void Rocket::HandlePostRenderUpdate(StringHash, VariantMap&)
{
    for (uint i = 0; i < rockets.Size(); i++)
    {
        if (rockets[i]->node_->IsEnabled())
        {
//            Rocket *rocket = rockets[i];
            //gDebugRenderer->AddSphere(Sphere(rockets[i]->node_->GetPosition(), 0.3f), Color::BLUE);

        }
    }
}

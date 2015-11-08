#include <stdafx.h>


#include "Missile.h"
#include "Core/Math.h"
#include "Game/Objects/Units/Tank/Tank.h"
#include "Game/Objects/Ammunition/AmmunitionEvents.h"
#include "Core/Camera.h"


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
        AnimateSmoke(timeStep);
    }
}

void Missile::Init(const Vector3 &speedShooter, const Vector3 &position, Tank *target)
{
    LoadFromFile();
    Normalize();
    CreateSmoke();

    this->target = target;
    this->position = position;
    speed = Vector3(0.0f, 1.0f, 0.0f);
    absSpeed = speedShooter.Length() * 1.5f;

    rotate = Quaternion(Vector3::UP, Vector3::UP);

    SubscribeToEvent(Urho3D::E_POSTRENDERUPDATE, HANDLER(Missile, HandlePostRenderUpdate));
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

    float k = 0.4f;
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

    node_->SetRotation(rotate);

    time += dT;
    distance += absSpeed * dT;

    if(position.y_ > heightBeginExcortTarget)
    {
        state = EscortTarget;
    }
}

void Missile::UpdateEscortTarget(float dT)
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

    if(angleNeed < 0.0f)
    {
        angleNeed = angleNeed;
    }

    if(angleNeed > 180.0f)
    {
        angleNeed = angleNeed;
    }

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
    node_->SetPosition(position);

    node_->SetRotation(rotate);

    if(time > rangeTime || distance > rangeDistance)
    {
        gScene->NodeRemoved(node_);
    }

    if((position - target->GetPosition()).Length() < 0.3f)
    {
        
        Sound *sound = gCache->GetResource<Sound>("Sounds/ExplosionMissile.wav");

        Node *nodeSource = node_->CreateChild("Source");
        SoundSource3D *soundSource = nodeSource->CreateComponent<SoundSource3D>();
        soundSource->SetDistanceAttenuation(1.0f, 150.0f, 1.0f);
        soundSource->SetSoundType(Urho3D::SOUND_EFFECT);
        soundSource->Play(sound);
        soundSource->SetAutoRemove(true);


        /*
        Vector3 posSource = nodeSource->GetWorldPosition();
        Vector3 posListener = gCamera->GetNode()->GetChild("Listener")->GetWorldPosition();
        Vector3 posCamera = gCamera->GetNode()->GetWorldPosition();

        float distanceListener = (posSource - posListener).Length();
        float distanceCamera = (posSource - posCamera).Length();

        LOGINFOF("posSource %s, posListener %s, posCamera %s, dist listener %f, dist camera %f", posSource.ToString().CString(), posListener.ToString().CString(), posCamera.ToString().CString(), distanceListener, distanceCamera);
        */

        VariantMap eventData = GetEventDataMap();
        eventData[AmmunitionEvent::P_TYPE] = Hit_Missile;
        eventData[AmmunitionEvent::P_OBJECT] = target;
        SendEvent(E_HIT, eventData);
        

        gScene->NodeRemoved(node_);
    }
}

void Missile::CreateSmoke()
{
    const uint NUM_BILLBOARDS = 50;

    Node *smokeNode = node_->CreateChild("Smoke");
    smokeNode->SetScale(1.0f);

    BillboardSet *billboardObject = smokeNode->CreateComponent<BillboardSet>();
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
    }

    billboardObject->Commit();

    Node *forEmitter = node_->CreateChild("Emitter");
    Node *forForEmitter = forEmitter->CreateChild("Emitter");

    ParticleEmitter *emitter = forForEmitter->CreateComponent<ParticleEmitter>();

    XMLFile xmlParticle = XMLFile(gContext);
    SharedPtr<File> file(gCache->GetFile("Particle/SnowExplosion.xml"));
    if(file)
    {
        bool res = xmlParticle.Load(*file);
        SharedPtr<ParticleEffect> pe(new ParticleEffect(gContext));
        XMLElement root = xmlParticle.GetRoot("particleemitter");
        res = pe->Load(root);

        emitter->SetEffect(pe);
        emitter->SetEmitting(true);
        emitter->Commit();
    }
}

void Missile::AnimateSmoke(float timeStep)
{
    PODVector<Node*> billboardNodes;

    node_->GetChildrenWithComponent<BillboardSet>(billboardNodes);

    const float BILLBOARD_ROTATION_SPEED = 50.0f;

    for(uint i = 0; i < billboardNodes.Size(); i++)
    {
        BillboardSet *billboardObject = billboardNodes[i]->GetComponent<BillboardSet>();

        for(uint j = 0; j < billboardObject->GetNumBillboards(); j++)
        {
            Billboard *bb = billboardObject->GetBillboard(j);
            bb->rotation_ += BILLBOARD_ROTATION_SPEED * timeStep;
        }
        billboardObject->Commit();
    }
}

void Missile::HandlePostRenderUpdate(StringHash, VariantMap&)
{
    return;

    SoundSource3D *soundSource = node_->GetComponent<SoundSource3D>();
    if(soundSource)
    {
        soundSource->DrawDebugGeometry(gDebugRenderer, true);
    }
}

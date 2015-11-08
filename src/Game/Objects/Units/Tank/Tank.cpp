#include <stdafx.h>


#include "Tank.h"
#include "Core/Math.h"
#include "Game/Objects/Terrain.h"
#include "GlobalFunctions.h"
#include "Game/Objects/Ammunition/Missile/Missile.h"
#include "GAme/Objects/Ammunition/AmmunitionEvents.h"


HashMap<Tank::Key, Tank::TankStruct> Tank::parameters;


Tank::Tank(Context *context) : GameObject(context)
{
    if (parameters.Empty())
    {
        parameters[Small] = TankStruct(Small, "Models/Tank.json");
        parameters[T_34_76] = TankStruct(T_34_76, "Models/T-34-76-2.json");
    }

    pathFinder.SetSize(gTerrain->NumRows(), gTerrain->NumCols());
    SubscribeToEvent(E_HIT, HANDLER(Tank, HandleAmmoHit));
}

void Tank::RegisterObject(Context* context)
{
    context->RegisterFactory<Tank>();
}

void Tank::Init(Type type_)
{
    translator.Init(this);
    type = type_;
    LoadFromFile();
    Normalize();
    ConfigurePhysics();
    CreateParticleEmitter();
}

void Tank::LoadFromFile()
{
    char *fileName = parameters[type].fileName;
    JSONFile *file = gCache->GetResource<JSONFile>(fileName);

    if (timeForReload)
    {
        gCache->ReloadResource(file);
    }

    JSONValue modelValue = file->GetRoot().Get("model");

    String fileModel = modelValue.Get("fileModel").GetString();
    String fileMaterials = modelValue.Get("fileMaterials").GetString();

    modelObject = node_->CreateComponent<StaticModel>();
    modelObject->SetModel(gCache->GetResource<Model>(fileModel));
    modelObject->ApplyMaterialList(fileMaterials);
    modelObject->SetCastShadows(true);

    speed = file->GetRoot().Get("speed").GetFloat();

    deltaRotate = file->GetRoot().Get("deltaRotate").GetFloat(); 

    Quaternion rotate(deltaRotate, Vector3::UP);
    node_->SetRotation(Quaternion(0, Vector3::UP));
    node_->Rotate(rotate);

    timeLastModified = GetLastModifiedTime(parameters[type].fileName);
}

void Tank::Normalize()
{
    Vector3 pos = GetPosition();
    node_->SetPosition({0.0f, 0.0f, 0.0f});
    node_->SetScale(1.0f);

    BoundingBox box = modelObject->GetModel()->GetBoundingBox();

    Vector3 delta = box.max_ - box.min_;

    float divider = Math::Max(delta.x_, delta.y_, delta.z_);

    float k = 1.0f;
    Vector3 scale = {k / divider, k / divider, k / divider};

    deltaPos.y_ = -box.min_.y_ / divider * k;
    deltaPos.z_ = -(box.max_.z_ + box.min_.z_) / 2.0f / divider * k;
    deltaPos.x_ = (box.max_.x_ + box.min_.x_) / 2.0f / divider * k;

    node_->SetScale(scale);

    SetPosition(pos);
}

void Tank::SetPosition(const Vector3& pos)
{
    node_->SetPosition(pos + deltaPos);
}

Vector3 Tank::GetPosition()
{
    return node_->GetPosition() - deltaPos;
}

void Tank::SetCoord(const Coord& coord)
{
    PODVector<Coord> path;
    path.Push(coord);
    translator.SetPath(path);
}

void Tank::Update(float dT)
{
    GameObject::Update(dT);

    if(timeElapsedAfterShoot != 0.0f)
    {
        timeElapsedAfterShoot += dT;
    }

    if(!translator.IsMoving())
    {
        if(inProcessFindPath)
        {
            if(pathFinder.PathIsFound())
            {
                PODVector<Coord> path = pathFinder.GetPath();
                SetPath(path);
                inProcessFindPath = false;
            }
        }
        else
        {
            float height = -1.0f;
            uint row = 0;
            uint col = 0;
            do
            {
                row = (uint)Math::RandomInt(0, (int)gTerrain->NumRows() - 1);
                col = (uint)Math::RandomInt(0, (int)gTerrain->NumCols() - 1);
                height = gTerrain->GetHeight(row, col);
            } while(height != 0.0f);

            Vector3 position = GetPosition();
            Coord start((uint)-position.z_, (uint)position.x_);
            pathFinder.StartFind(start, {row, col});
            inProcessFindPath = true;
        }
        return;
    }

    SetPosition(translator.Update(dT));

    if (timeForReload)
    {
        int time = (int)gTime->GetElapsedTime();
        if (time - timeLastReload >= timeForReload)
        {
            if (GetLastModifiedTime(parameters[type].fileName) != timeLastModified)
            {
                Init(type);
            }
            timeLastReload = time;
        }
    }
}

void Tank::SetSelected(bool selected_)
{
     selected = selected_;
}

bool Tank::IsSelected()
{
    return selected;
}

void Tank::SetPath(PODVector<Coord> &path)
{
    translator.SetPath(path, speed);
}

void Tank::SetRotation(float rotation)
{
    Quaternion rotate(deltaRotate + rotation, Vector3::UP);
    node_->SetRotation(rotate);
}

float Tank::GetRotation()
{
    float ret = node_->GetRotation().YawAngle() - deltaRotate;
    return ret > 0 ? ret : ret + 360.0f;
}

SharedPtr<Tank> Tank::Create(Type type)
{
    SharedPtr<Node> node(gScene->CreateChild(NODE_TANK));
    SharedPtr<Tank> tank(node->CreateComponent<Tank>());
    tank->Init(type);
    return tank;
}

void Tank::HandleCollision(StringHash, VariantMap& eventData)
{
    if(timeElapsedAfterShoot < timeRechargeWeapon)
    {
        return;
    }

    Node *node = (Node*)eventData[Urho3D::NodeCollisionStart::P_OTHERNODE].GetPtr();

    if(node->GetName() == NODE_TANK)
    {
        SharedPtr<Missile> missile(Missile::Create(translator.speed, translator.currentPos, node->GetComponent<Tank>()));
        timeElapsedAfterShoot = 1e-6f;
    }
}

void Tank::HandleAmmoHit(StringHash, VariantMap& eventData)
{
    Tank *tank = (Tank*)eventData[AmmunitionEvent::P_OBJECT].GetPtr();

    if(tank != this)
    {
        return;
    }

    PODVector<Node*> emitterNodes;
    node_->GetChildrenWithComponent<ParticleEmitter>(emitterNodes);

    emitterNodes[0]->GetComponent<ParticleEmitter>()->SetEmitting(true);
}

void Tank::CreateParticleEmitter()
{
    Node *forEmitter = node_->CreateChild("Emitter");
    forEmitter->SetWorldScale((Vector3::ONE / node_->GetScale() / 5.0f));

    ParticleEmitter *emitter = forEmitter->CreateComponent<ParticleEmitter>();

    XMLFile xmlParticle = XMLFile(gContext);
    SharedPtr<File> file(gCache->GetFile("Particle/SnowExplosion.xml"));
    if(file)
    {
        bool res = xmlParticle.Load(*file);
        SharedPtr<ParticleEffect> pe(new ParticleEffect(gContext));
        XMLElement root = xmlParticle.GetRoot("particleemitter");
        res = pe->Load(root);
        emitter->SetEffect(pe);
        emitter->SetEmitting(false);
    }
}

void Tank::ConfigurePhysics()
{
    // WARN
    // Wrong control. It is necessary to create the trigger and a body which will influence it
    // http://www.gamedev.ru/community/urho3d/forum/?id=204570&page=4
    RigidBody *body = node_->GetComponent<RigidBody>();
    if(body)
    {
        node_->RemoveComponent(body);
        node_->RemoveComponent(node_->GetComponent<CollisionShape>());
    }
    else
    {
        SubscribeToEvent(node_, Urho3D::E_NODECOLLISION, HANDLER(Tank, HandleCollision));
    }

    body = node_->CreateComponent<RigidBody>();
    body->SetMass(1.0f);
    body->SetTrigger(true);
    CollisionShape *shape = node_->CreateComponent<CollisionShape>();
    shape->SetSphere(radiusDetect / node_->GetScale().x_);
}

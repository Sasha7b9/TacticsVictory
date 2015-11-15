#include <stdafx.h>


#include "Tank.h"
#include "Core/Math.h"
#include "Game/Objects/Terrain.h"
#include "GlobalFunctions.h"
#include "Game/Objects/Ammo/Rocket/Rocket.h"
#include "GAme/Objects/GameObjectEvents.h"
#include "Game/Particles.h"


HashMap<Tank::Key, Tank::TankStruct> Tank::parameters;


Tank::Tank(Context *context) : 
    UnitObject(context)
{
    if (parameters.Empty())
    {
        parameters[Small] = TankStruct(Small, "Models/Tank.json");
        parameters[T_34_76] = TankStruct(T_34_76, "Models/T-34-76-2.json");
    }



    pathFinder.SetSize(gTerrain->NumRows(), gTerrain->NumCols());

    SubscribeToEvent(E_HIT, URHO3D_HANDLER(Tank, HandleAmmoHit));

    rocketLauncher = new RocketLauncher(gContext, this);
}

void Tank::RegisterObject(Context* context)
{
    context->RegisterFactory<Tank>();
}

void Tank::Init(Type type_)
{
    node_->SetVar("PointerTank", this);

    translator.Init(this);
    type = type_;
    LoadFromFile();
    Normalize();

    rocketLauncher->Init();
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
    modelObject->SetViewMask(VIEW_MASK_FOR_MISSILE);
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
    gProfiler->BeginBlock("Tank::Update");
    GameObject::Update(dT);

    rocketLauncher->Update(dT);

    if(!translator.IsMoving())
    {
        /*
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
        */
    }
    else
    {
        SetPosition(translator.Update(dT));
    }

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

    gProfiler->EndBlock();
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

void Tank::HandleAmmoHit(StringHash, VariantMap& eventData)
{
    Tank *tank = (Tank*)eventData[AmmoEvent::P_OBJECT].GetPtr();

    if(tank != this)
    {
        return;
    }

    Particles::Emitting(Particle_Explosion, node_->GetPosition());
}

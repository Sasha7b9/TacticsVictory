﻿/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"
#include "Scene/Objects/Units/Tank/_Tank.h"
#include "Core/_Math.h"
//#include "GlobalFunctions.h"
#include "Scene/Objects/Ammo/Rocket/Rocket.h"
#include "Scene/Objects/_GameObjectEvents.h"
#include "Game/Particles.h"
#include "GUI/Cursor.h"
#include "GUI/GuiGame/ContextMenuUnit.h"



HashMap<Tank::Key, Tank::TankStruct> Tank::parameters;
PODVector<Tank*> Tank::allTanks;



Tank::Tank(Context *context) : UnitObject(context)
{
    name = "Tank";
    type = GameObject::Unit;

    if (parameters.Empty())
    {
        parameters[Small] = TankStruct(Small, "Models/Tank.json");
        parameters[T_34_76] = TankStruct(T_34_76, "Models/T-34-76-2.json");
    }

    SubscribeToEvent(E_HIT, URHO3D_HANDLER(Tank, HandleAmmoHit));

    rocketLauncher = new RocketLauncher(TheContext, this);
}


Tank::~Tank()
{

}


void Tank::RegisterObject(Context* context)
{
    context->RegisterFactory<Tank>();
}


void Tank::RegisterInAS()
{
    asIScriptEngine *engine = TheScript->GetScriptEngine();
    engine->RegisterObjectType("Tank", 0, asOBJ_REF);
#pragma warning(push)
#pragma warning(disable:4191)
    engine->RegisterObjectBehaviour("Tank", asBEHAVE_ADDREF, "void AddRef()", asMETHOD(Tank, AddRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("Tank", asBEHAVE_RELEASE, "void ReleaseRef()", asMETHOD(Tank, ReleaseRef), asCALL_THISCALL);
    engine->RegisterObjectProperty("Tank", "bool inProcessFindPath", offsetof(Tank, inProcessFindPath)); //-V107
    engine->RegisterObjectProperty("Tank", "WaveAlgorithm@ pathFinder", offsetof(Tank, pathFinder)); //-V107
#pragma warning(pop)
}


void Tank::Init(TypeTank type_, uint _id_)
{
    node_->SetVar("PointerTank", this);

    pathFinder = new WaveAlgorithm();
    pathFinder->SetSize(TheTerrain->NumRows(), TheTerrain->NumCols());

    translator->Init(this);
    typeTank = type_;
    LoadFromFile();
    Normalize();

    id = (_id_ == 0) ? id : _id_;

    rocketLauncher->Init();

//    ScriptInstance *instance = node_->CreateComponent<ScriptInstance>();
//
//    LOGINFO("Загружаю Tank.as");
//
//    ScriptFile *script = TheCache->GetResource<ScriptFile>("Models/Units/Tank/Tank.as");
//
//    LOGINFO("Tank.as загружен");
//
//    instance->CreateObject(script, "TankUpdater");
//    VariantVector params;
//    params.Push(Variant(rocketLauncher));
//    params.Push(Variant(translator));
//    params.Push(Variant(this));
//    instance->Execute("void SetRotationSpeed(RocketLauncher@ launch, Translator@ trans, Tank@ tan)", params);

    /*
    params.Clear();
    params.Push(Variant(pathFinder));
    instance->Execute("void SetWaveAlgorithm(WaveAlgorithm@ wave)", params);
    */
}


void Tank::LoadFromFile()
{
    char *fileName = parameters[typeTank].fileName; //-V108 //-V2006
    JSONFile *file = TheCache->GetResource<JSONFile>(fileName);

    if (timeForReload)
    {
        TheCache->ReloadResource(file);
    }

    JSONValue &root = file->GetRoot();
    JSONValue modelValue = root.Get("model");

    String fileModel = modelValue.Get("fileModel").GetString();
    String fileMaterials = modelValue.Get("fileMaterials").GetString();

    modelObject = node_->CreateComponent<StaticModel>();
    modelObject->SetViewMask(VIEW_MASK_FOR_MISSILE);
    modelObject->SetModel(TheCache->GetResource<Model>(fileModel));
    modelObject->ApplyMaterialList(fileMaterials);
    modelObject->SetCastShadows(true);

    speed = root.Get("speed").GetFloat();

    deltaRotate = root.Get("deltaRotate").GetFloat(); 

    Quaternion rotate(deltaRotate, Vector3::UP);
    node_->SetRotation(Quaternion(0, Vector3::UP));
    node_->Rotate(rotate);

    timeLastModified = GetLastModifiedTime(parameters[typeTank].fileName); //-V108 //-V2006
}


void Tank::SetCoord(const Coord& coord)
{
    PODVector<Coord> path;
    path.Push(coord);
    translator->SetPath(path);
}


void Tank::Update(float dT)
{
    TheProfiler->BeginBlock("Tank::Update");
    GameObject::Update(dT);

    //rocketLauncher->Update(dT);

    if(!translator->IsMoving())
    {
        if(inProcessFindPath)
        {
            if(pathFinder->PathIsFound())
            {
                PODVector<Coord> path = pathFinder->GetPath();
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
                row = static_cast<uint>(Math::RandomInt(0, static_cast<int>(TheTerrain->NumRows()) - 1));
                col = static_cast<uint>(Math::RandomInt(0, static_cast<int>(TheTerrain->NumCols()) - 1));
                height = TheTerrain->GetHeight(row, col);
            } while(fabs(height) > M_EPSILON);

            Vector3 position = GetPosition();
            Coord start(static_cast<uint>(-position.z_), static_cast<uint>(position.x_));
            pathFinder->StartFind(start, {row, col});
            inProcessFindPath = true;
        }
    }
    else
    {
        SetPosition(translator->Update(dT));
    }

    if (timeForReload)
    {
        int time = static_cast<int>(TheTime->GetElapsedTime());
        if (time - timeLastReload >= timeForReload)
        {
            if (GetLastModifiedTime(parameters[typeTank].fileName) != timeLastModified) //-V108
            {
                Init(typeTank, id);
            }
            timeLastReload = time;
        }
    }

    TheProfiler->EndBlock();
}


void Tank::SetPath(const PODVector<Coord> &path)
{
    translator->SetPath(path, speed);
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


SharedPtr<Tank> Tank::Create(TypeTank typeTank, uint _id_)
{
    SharedPtr<Node> node(TheScene->CreateChild(NODE_TANK, LOCAL));
    SharedPtr<Tank> tank(node->CreateComponent<Tank>(LOCAL));

    tank->Init(typeTank, _id_);
    allTanks.Push(tank);
    return tank;
}


void Tank::HandleAmmoHit(StringHash, VariantMap& eventData)
{
    Tank *tank = dynamic_cast<Tank*>(eventData[AmmoEvent::P_OBJECT].GetPtr());

    if(tank != this)
    {
        return;
    }

    Particles::EmittingDinamic(Explosion_Tank, node_);

    Particles::EmittingDinamic(Fire_Tank, node_);
}


Node* Tank::GetNode()
{
    return node_;
}


PODVector<Tank*>& Tank::GetAll()
{
    return allTanks;
}


Tank* Tank::GetByID(uint id)
{
    for(Tank *tank : allTanks)
    {
        if(tank->GetID() == id)
        {
            return tank;
        }
    }
    return nullptr;
}

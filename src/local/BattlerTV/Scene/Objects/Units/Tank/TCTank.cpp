// 2021/02/17 15:45:38 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#include "stdafx.h"


void CTank::RegisterObject(Context *context)
{
    context->RegisterFactory<CTank>();
}


void CTank::RegisterInAS()
{
    asIScriptEngine *engine = TheScript->GetScriptEngine();
    engine->RegisterObjectType("CTank", 0, asOBJ_REF);
#pragma warning(push)
#pragma warning(disable:4191)
    engine->RegisterObjectBehaviour("CTank", asBEHAVE_ADDREF, "void AddRef()", asMETHOD(Tank, AddRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("CTank", asBEHAVE_RELEASE, "void ReleaseRef()", asMETHOD(Tank, ReleaseRef), asCALL_THISCALL);
    engine->RegisterObjectProperty("CTank", "bool inProcessFindPath", offsetof(CTank, inProcessFindPath));
#pragma warning(pop)

    engine->RegisterObjectProperty("CTank", "WaveAlgorithm@ pathFinder", offsetof(CTank, pathFinder));
}


void CTank::Init(Type::E _typeTank, uint _id_)
{
    pathFinder = new WaveAlgorithm();
    pathFinder->SetSize(TheTerrain->NumRows(), TheTerrain->NumCols());

    Tank::Init(_typeTank, _id_);
}


SharedPtr<CTank> CTank::Create(Type::E typeTank, uint _id_)
{
    SharedPtr<Node> node(TheScene->scene->CreateChild(NODE_TANK, LOCAL));
    SharedPtr<CTank> tank(node->CreateComponent<CTank>(LOCAL));

    tank->Init(typeTank, _id_);
    allTanks.Push(tank);
    return tank;
}


void CTank::Update(float dT)
{
    Tank::Update(dT);

    if (!translator->IsMoving())
    {
        if (inProcessFindPath)
        {
            if (pathFinder->PathIsFound())
            {
                PODVector<Coord> path = pathFinder->GetPath();
                SetPath(path);
                inProcessFindPath = false;
            }
        }
        else
        {
//            Vector3 position = GetPosition();
//            Coord start(static_cast<uint>(-position.z_), static_cast<uint>(position.x_));
//
//            pathFinder->StartFind(start, { row, col });
//            inProcessFindPath = true;
        }
    }
}

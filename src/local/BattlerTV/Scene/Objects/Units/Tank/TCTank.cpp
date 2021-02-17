// 2021/02/17 15:45:38 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#include "stdafx.h"


void CTank::RegisterObject(Context *context)
{
    context->RegisterFactory<CTank>();
}


void CTank::RegisterInAS()
{
    Tank::RegisterInAS();

    asIScriptEngine *engine = TheScript->GetScriptEngine();
    engine->RegisterObjectType("CTank", 0, asOBJ_REF);

    engine->RegisterObjectProperty("CTank", "WaveAlgorithm@ pathFinder", offsetof(CTank, pathFinder));
}


void CTank::Init(TypeTank _typeTank, uint _id_)
{
    pathFinder = new WaveAlgorithm();
    pathFinder->SetSize(TheTerrain->NumRows(), TheTerrain->NumCols());

    Tank::Init(_typeTank, _id_);
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

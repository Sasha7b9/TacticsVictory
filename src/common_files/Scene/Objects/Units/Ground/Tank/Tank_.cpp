// 2021/02/22 15:40:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#include "stdafx.h"
#include "Scene/Objects/Units/UnitsEvents_.h"
#include "Scene/Objects/Units/Accessories/Engine/Engine_.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"


Vector<Tank *> Tank::storage;


static const MinPP minTank{ 0.0f };
static const MaxPP maxTank{ 1.0f, 120.0f, 10.0f };


Tank::Tank(Context *context) :
    GroundUnit(context, minTank, maxTank)
{
    storage.Push(this);
}


void Tank::RegisterObject()
{
    TheContext->RegisterFactory<Tank>();
}


void Tank::OnNodeSet(Node *node)
{
    Unit::OnNodeSet(node ? node_ : node);
}


void Tank::Start()
{
    Unit::Start();

    node_->SetVar(VAR_NODE_IS_FLYING, false);

    if (!LoadFromJSON("Models/Units/Ground/Tank/Tank.json"))
    {
        LOGERRORF("Can not load json file");
        return;
    }

    Normalize();

    engine = new EngineGround(this);
}


void Tank::Update(float dT)
{
    Unit::Update(dT);
}


void Tank::Compress(VectorBuffer &buffer)
{
    Unit::Compress(buffer);
}


void Tank::Decompress(MemoryBuffer &buffer)
{
    Unit::Decompress(buffer);
}

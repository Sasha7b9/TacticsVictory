// 2021/02/22 15:40:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#include "stdafx.h"
#include "Scene/Objects/Units/UnitsEvents_.h"
#include "Scene/Objects/Units/Accessories/Engine/Engine_.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"


Vector<Tank *> Tank::storage;


Tank::Tank(Context *context) : Unit(context)
{
    storage.Push(this);
}


void Tank::RegisterComponent()
{
    TheContext->RegisterFactory<Tank>();
}


void Tank::Start()
{
    Unit::Start();

    node_->SetVar(VAR_NODE_IS_FLYING, false);

    if (!LoadFromJSON())
    {
        LOGERRORF("Can not load json file");
        return;
    }

    Normalize();

    engine = new EngineGround(this);
}


void Tank::OnNodeSet(Node *node)
{
    Unit::OnNodeSet(node ? node_ : node);
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

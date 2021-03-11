// 2021/02/22 20:46:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Air/AirPlane/AirPlane_.h"


Vector<AirPlane *> AirPlane::storage;


static const MinPP minAirPlane{ 8.0f };
static const MaxPP maxAirPlane{ 10.0f, 1200.0f, 10.0f };


AirPlane::AirPlane(Context *context) :
    Unit(context, minAirPlane, maxAirPlane)
{
    storage.Push(this);
}


void AirPlane::RegisterComponent()
{
    TheContext->RegisterFactory<AirPlane>();
}


void AirPlane::OnNodeSet(Node *node)
{
    Unit::OnNodeSet(node ? node_ : node);
}


void AirPlane::Start()
{
    Unit::Start();

    node_->SetVar(VAR_NODE_IS_FLYING, true);

    if (!LoadFromJSON("Models/Units/Air/AirPlane/AirPlane.json"))
    {
        LOGERRORF("Can not load json file");
        return;
    }

    Normalize();

    engine = new EngineAir(this);
}


void AirPlane::Compress(VectorBuffer &buffer)
{
    Unit::Compress(buffer);
}


void AirPlane::Decompress(MemoryBuffer &buffer)
{
    Unit::Decompress(buffer);
}


void AirPlane::Update(float dT)
{
    Unit::Update(dT);
}

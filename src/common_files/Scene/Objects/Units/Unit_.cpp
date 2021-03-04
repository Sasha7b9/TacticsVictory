// 2021/02/22 15:46:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Accessories/Accessories_.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Scene/Objects/Units/Unit_.h"


Vector<UnitObject *> UnitObject::storage;


UnitObject::UnitObject(Context *context) : ObjectT(context)
{
    storage.Push(this);
}


void UnitObject::Start()
{
    ObjectT::Start();

    node_->SetVar(VAR_NODE_IS_UNIT, true);
}


void UnitObject::Update(float timeStep)
{
    ObjectT::Update(timeStep);
}


void UnitObject::Compress(VectorBuffer &buffer)
{
    ObjectT::Compress(buffer);
}


void UnitObject::Decompress(MemoryBuffer &buffer)
{
    ObjectT::Decompress(buffer);
}

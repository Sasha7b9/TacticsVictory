// 2021/02/22 15:46:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Scene/Objects/Units/Unit_.h"


Vector<Unit *> Unit::storage;


Unit::Unit(Context *context) : ObjectT(context)
{
    storage.Push(this);
}


void Unit::Start()
{
    ObjectT::Start();

    node_->SetVar(VAR_NODE_IS_UNIT, true);
}


void Unit::Update(float timeStep)
{
    ObjectT::Update(timeStep);
}


void Unit::Compress(VectorBuffer &buffer, bool log)
{
    ObjectT::Compress(buffer, log);
}


void Unit::Decompress(MemoryBuffer &buffer, bool log)
{
    ObjectT::Decompress(buffer, log);
}

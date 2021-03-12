// 2021/02/22 15:46:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Scene/Objects/Units/Unit_.h"


Vector<Unit *> Unit::storage;


Unit::Unit(Context *context, const MinPP &min, const MaxPP &max) : ObjectT(context, min, max)
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


void Unit::Compress(VectorBuffer &buffer)
{
    ObjectT::Compress(buffer);
}


void Unit::Decompress(MemoryBuffer &buffer)
{
    ObjectT::Decompress(buffer);
}


bool Unit::CanMoveTo(float rowX, float colZ) const
{
    if (colZ < 0.0f || rowX < 0.0f || colZ >= TheTerrain->WidthZ() || rowX >= TheTerrain->HeightX())
    {
        return false;
    }

    if (IsFlying())
    {
        if (physics->pos.GetAltitude() >= TheTerrain->GetHeight(physics->pos.GetCoord()))
        {
            return true;
        }
    }

    return TheTerrain->GetHeight(physics->pos.GetCoord()) ==
        TheTerrain->GetHeight(rowX, colZ);
}


bool Unit::TooCloseToAnoterUnit() const
{
    Vector3 position = physics->pos.GetWorld();

    physics->pos.CalculateDistanceFromCenter();

    float distance = physics->pos.distanceFromCenter;

    for (Unit *unit : Unit::storage)
    {
        if (unit != this)
        {
            if (std::fabs(distance - unit->physics->pos.distanceFromCenter) > 2.0f)
            {
                continue;
            }

            if (position.DistanceToPoint(unit->physics->pos.GetWorld()) < 0.9f)
            {
                return true;
            }
        }
    }

    return false;
}

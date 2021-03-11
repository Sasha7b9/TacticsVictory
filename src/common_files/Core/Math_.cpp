// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Core/Math_.h"


int Math::CircularIncrease(int value, int min, int max)
{
    ++value;
    return (value > max) ? min : value;
}


BoundingBox Math::CalculateBoundingBox(const float *buffer, uint numVertexes)
{
    BoundingBox box(1e6f, -1e6f);

    for(uint i = 0; i < numVertexes; i++)
    {
        box.Merge(Vector3(buffer + static_cast<uint64>(i) * 8));
    }

    return box;
}


uint Math::RandomUINT(float range)
{
    return (uint)Random(range);
}

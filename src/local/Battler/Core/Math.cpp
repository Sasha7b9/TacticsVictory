// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "Math.h"



int Math::CircularIncrease(int value, int min, int max)
{
    ++value;
    return (value > max) ? min : value;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
BoundingBox Math::CalculateBoundingBox(const float *buffer, uint numVertexes)
{
    BoundingBox box(1e6f, -1e6f);

    for(uint i = 0; i < numVertexes; i++)
    {
        box.Merge(Vector3(buffer + static_cast<uint64>(i * 8)));
    }

    return box;
}

#include <stdafx.h>


#include "Plane.h"
#include "Core/Math.h"
#include "Game/Objects/Line.h"


lPlane lPlane::ZERO = lPlane(Vector3::ZERO, Vector3::ZERO, Vector3::ZERO, Vector3::ZERO);


lPlane::lPlane(const Vector3 &v0_ /* = Vector3::ZERO */, const Vector3 &v1_ /* = Vector3::ZERO */, const Vector3 &v2_ /* = Vector3::ZERO */, const Vector3 &v3_ /* = Vector3::ZERO */)
{
    v0 = v0_;
    v1 = v1_;
    v2 = v2_;
    v3 = v3_;
}

bool lPlane::IsEquals(const lPlane &plane)
{
    return v0 == plane.v0 && v1 == plane.v1 && v2 == plane.v2 && v3 == plane.v3;
}

bool lPlane::IsZero()
{
    return v0 == Vector3::ZERO && v1 == Vector3::ZERO && v2 == Vector3::ZERO && v3 == Vector3::ZERO;
}

void lPlane::CalculateRowCol()
{
    float xMin = Math::Min(v0.x_, v1.x_, v2.x_, v3.x_);
    float xMax = Math::Max(v0.x_, v1.x_, v2.x_, v3.x_);
    float zMin = Math::Min(-v0.z_, -v1.z_, -v2.z_, -v3.z_);
    float zMax = Math::Max(-v0.z_, -v1.z_, -v2.z_, -v3.z_);
    
    col = (uint)((xMax + xMin) / 2.0f);
    row = (uint)((zMin + zMax) / 2.0f);
}

void lPlane::SetY(float y)
{
    v0.y_ = v1.y_ = v2.y_ = v3.y_ = y;
}

lLine lPlane::NearEdge(Ray &ray)
{
    lLine lines[] =
    {
        lLine(v0, v1),
        lLine(v1, v2),
        lLine(v2, v3),
        lLine(v3, v0)
    };

    int index = -1;

    float distance = 1e3f;

    for (int i = 0; i < 4; i++)
    {
        Ray rayEdge(lines[i].start, lines[i].end - lines[i].start);
        Vector3 closestPoint = ray.ClosestPoint(rayEdge);
        float dist = rayEdge.Distance(closestPoint);
        if (dist < distance)
        {
            distance = dist;
            index = i;
        }
    }

    return lLine(lines[index].start, lines[index].end);
}

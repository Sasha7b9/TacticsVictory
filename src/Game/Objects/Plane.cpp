#include <stdafx.h>


#include "Plane.h"


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
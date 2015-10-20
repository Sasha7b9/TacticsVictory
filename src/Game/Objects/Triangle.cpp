#include <stdafx.h>


#include "Triangle.h"


vTriangle vTriangle::ZERO = vTriangle(Vector3::ZERO, Vector3::ZERO, Vector3::ZERO);


vTriangle::vTriangle(const Vector3 &v0_, const Vector3 &v1_, const Vector3 &v2_)
{
    v0 = v0_;
    v1 = v1_;
    v2 = v2_;
}

bool vTriangle::IsEquals(const vTriangle &triangle)
{
    return v0 == triangle.v0 && v1 == triangle.v1 && v2 == triangle.v2;
}

bool vTriangle::IsZero()
{
    return v0 == Vector3::ZERO && v1 == Vector3::ZERO && v2 == Vector3::ZERO;
}
#include <stdafx.h>


#include "Triangle.h"


lTriangle lTriangle::ZERO = lTriangle(Vector3::ZERO, Vector3::ZERO, Vector3::ZERO);


lTriangle::lTriangle(const Vector3 &v0_, const Vector3 &v1_, const Vector3 &v2_)
{
    v0 = v0_;
    v1 = v1_;
    v2 = v2_;
}

bool lTriangle::IsEquals(const lTriangle &triangle)
{
    return v0 == triangle.v0 && v1 == triangle.v1 && v2 == triangle.v2;
}

bool lTriangle::IsZero()
{
    return v0 == Vector3::ZERO && v1 == Vector3::ZERO && v2 == Vector3::ZERO;
}
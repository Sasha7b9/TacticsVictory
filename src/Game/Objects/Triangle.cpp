#include <stdafx.h>


#include "Triangle.h"


tvTriangle tvTriangle::ZERO = tvTriangle(Vector3::ZERO, Vector3::ZERO, Vector3::ZERO);


tvTriangle::tvTriangle(const Vector3 &v0_, const Vector3 &v1_, const Vector3 &v2_)
{
    v0 = v0_;
    v1 = v1_;
    v2 = v2_;
}

bool tvTriangle::IsEquals(const tvTriangle &triangle)
{
    return v0 == triangle.v0 && v1 == triangle.v1 && v2 == triangle.v2;
}

bool tvTriangle::IsZero()
{
    return v0 == Vector3::ZERO && v1 == Vector3::ZERO && v2 == Vector3::ZERO;
}
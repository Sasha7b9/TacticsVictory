// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Primitives/TTriangle_.h"


Triangle Triangle::ZERO = Triangle(Vector3::ZERO, Vector3::ZERO, Vector3::ZERO);


Triangle::Triangle(const Vector3 &v0_, const Vector3 &v1_, const Vector3 &v2_) : v0(v0_), v1(v1_), v2(v2_)
{
}


bool Triangle::IsEquals(const Triangle &triangle)
{
    return v0 == triangle.v0 && v1 == triangle.v1 && v2 == triangle.v2;
}


bool Triangle::IsZero()
{
    return v0 == Vector3::ZERO && v1 == Vector3::ZERO && v2 == Vector3::ZERO;
}
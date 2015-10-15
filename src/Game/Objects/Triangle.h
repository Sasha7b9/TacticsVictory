#pragma once


class tvTriangle
{
public:
    tvTriangle(const Vector3 &v0 = Vector3::ZERO, const Vector3 &v1 = Vector3::ZERO, const Vector3 &v2 = Vector3::ZERO);

    bool IsEquals(const tvTriangle &triangle);
    bool IsZero();

    Vector3 v0;
    Vector3 v1;
    Vector3 v2;

    static tvTriangle ZERO;
};
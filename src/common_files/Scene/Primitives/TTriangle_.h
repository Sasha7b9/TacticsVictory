// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Triangle
{
public:
    Triangle(const Vector3 &v0 = Vector3::ZERO, const Vector3 &v1 = Vector3::ZERO, const Vector3 &v2 = Vector3::ZERO);

    bool IsEquals(const Triangle &triangle);
    bool IsZero();

    Vector3 v0;
    Vector3 v1;
    Vector3 v2;

    static Triangle ZERO;
};
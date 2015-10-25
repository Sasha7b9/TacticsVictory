#pragma once


class lPlane
{
public:
    lPlane(const Vector3 &v0 = Vector3::ZERO, const Vector3 &v1 = Vector3::ZERO, const Vector3 &v2 = Vector3::ZERO, const Vector3 &v3 = Vector3::ZERO);

    bool IsEquals(const lPlane &plane);
    bool IsZero();
    void CalculateRowCol();

    Vector3 v0;
    Vector3 v1;
    Vector3 v2;
    Vector3 v3;

    uint row = 0;
    uint col = 0;

    static lPlane ZERO;
};
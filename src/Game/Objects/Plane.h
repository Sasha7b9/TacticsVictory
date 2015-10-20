#pragma once


class vPlane
{
public:
    vPlane(const Vector3 &v0 = Vector3::ZERO, const Vector3 &v1 = Vector3::ZERO, const Vector3 &v2 = Vector3::ZERO, const Vector3 &v3 = Vector3::ZERO);

    bool IsEquals(const vPlane &plane);
    bool IsZero();

    Vector3 v0;
    Vector3 v1;
    Vector3 v2;
    Vector3 v3;

    uint row = 0;
    uint col = 0;

    static vPlane ZERO;
};
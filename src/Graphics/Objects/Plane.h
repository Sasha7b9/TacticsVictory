#pragma once


class Plane
{
public:
    Plane(const Vector3 &v0 = Vector3::ZERO, const Vector3 &v1 = Vector3::ZERO, const Vector3 &v2 = Vector3::ZERO, const Vector3 &v3 = Vector3::ZERO);

    bool IsEquals(const Plane &plane);
    bool IsZero();
    void CalculateRowCol();
    void SetY(float y);
    Line NearEdge(URay &ray);

    Vector3 v0;
    Vector3 v1;
    Vector3 v2;
    Vector3 v3;

    uint row = 0;
    uint col = 0;

    static Plane ZERO;
};
// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Primitives/Line_.h"


class TPlane
{
public:
    TPlane(const Vector3 &v0 = Vector3::ZERO, const Vector3 &v1 = Vector3::ZERO, const Vector3 &v2 = Vector3::ZERO,
        const Vector3 &v3 = Vector3::ZERO);

    bool IsEquals(const TPlane &plane);
    bool IsZero();
    void CalculateRowCol();
    void SetY(float y);
    Line NearEdge(const Ray &ray);

    Vector3 v0;
    Vector3 v1;
    Vector3 v2;
    Vector3 v3;

    uint row = 0;
    uint col = 0;

    static TPlane ZERO;
};

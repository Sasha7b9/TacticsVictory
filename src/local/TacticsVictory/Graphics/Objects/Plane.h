/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Line.h"


class PlaneRTS
{
public:
    PlaneRTS(const Vector3 &v0 = Vector3::ZERO, const Vector3 &v1 = Vector3::ZERO, const Vector3 &v2 = Vector3::ZERO, const Vector3 &v3 = Vector3::ZERO);

    bool IsEquals(const PlaneRTS &plane);
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

    static PlaneRTS ZERO;
};

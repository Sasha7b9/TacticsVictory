// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Line
{
public:
    Line(const Vector3 &start = Vector3::ZERO, const Vector3 &end = Vector3::ZERO);

    bool IsEquals(const Line &line);
    bool IsZero();

    Vector3 start;
    Vector3 end;

    static Line ZERO;
};

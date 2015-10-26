#pragma once


class lLine
{
public:
    lLine(const Vector3 &start = Vector3::ZERO, const Vector3 &end = Vector3::ZERO);

    bool IsEquals(const lLine &line);
    bool IsZero();

    Vector3 start;
    Vector3 end;

    static lLine ZERO;
};

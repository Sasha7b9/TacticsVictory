#pragma once


class Translator
{
public:
    void Set(const Vector3 &start, const Vector3 &end, float speed);
    Vector3 Update(float dT, bool *inMovingState);

private:
    Vector3 end;
    Vector3 currentPos;
    Vector3 speed;
    float absSpeed = 0.0f;
    float distance = 0.0f;
};
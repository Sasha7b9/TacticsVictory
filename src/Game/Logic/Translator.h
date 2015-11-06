#pragma once


#include "Game/Path/WaveAlgorithm.h"


class Translator
{
public:
    Translator();

    void Init(Tank* tank);

    void SetPath(PODVector<Coord> &path, float speed = 0.0f);

    Vector3 Update(float dT);

    bool IsMoving();

private:

    enum State
    {
        Move,
        Rotate,
        Stop
    };

    Vector3 end;
    Vector3 currentPos;
    Vector3 speed;

    State state = Stop;

    PODVector<Coord> path;

    float absSpeed = 0.0f;
    float distance = 0.0f;

    float speedRotate = 180.0f;
    float absAngle = 0.0f;
    float currentAngle = 0.0f;
    float endAngle = 0.0f;

    VariantMap angles;

    Tank *tank = nullptr;

    void SetStep(Coord &start, Coord &end);
    void StartRotation(float angleNeed);

    Translator& operator=(const Translator&)
    {};
};
#pragma once
#include "Game/Path/WaveAlgorithm.h"



class Translator : public Object
{
    URHO3D_OBJECT(Translator, Object)

    friend class Tank;

public:
    Translator(Context *context = gContext);

    static void RegisterInAS();
    void Init(Tank* tank);
    void SetPath(const PODVector<Coord> &path, float speed = 0.0f);
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

    Tank *tank = nullptr; //-V122

    void SetStep(const Coord &start, const Coord &end);
    void StartRotation(float angleNeed);

    DEFAULT_MEMBERS(Translator);
};

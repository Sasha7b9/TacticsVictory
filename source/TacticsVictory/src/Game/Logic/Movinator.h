#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Movinator : public LogicComponent
{
    URHO3D_OBJECT(Movinator, LogicComponent);

public:
    Movinator(Context *context);
    void SetMoveSpeed(float speed);
    void SetCenter(const Vector3 &vec);
    virtual void Update(float time);

private:
    float speed = 0.0f;
    float angle = 0.0f;
    Vector3 center = Vector3::ZERO;
};

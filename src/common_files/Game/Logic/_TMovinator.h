/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once


extern Context *TheContext;


class Movinator : public LogicComponent
{
    URHO3D_OBJECT(Movinator, LogicComponent);

public:
    Movinator(Context *context = TheContext);
    void SetMoveSpeed(float speed);
    void SetCenter(const Vector3 &vec);
    virtual void Update(float time);

    static void RegisterObject(Context *context = TheContext);

private:
    float speed = 0.0f;
    float angle = 0.0f;
    Vector3 center = Vector3::ZERO;
};

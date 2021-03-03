// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


// ”правл€ет движением солнца
class SunEngine : public LogicComponent
{
    URHO3D_OBJECT(SunEngine, LogicComponent);

public:
    SunEngine(Context *context = TheContext);
    void SetMoveSpeed(float speed);
    void SetCenter(const Vector3 &vec);
    virtual void Update(float time);

    static void RegisterComponent(Context *context = TheContext);

private:
    float speed = 0.0f;
    float angle = 0.0f;
    Vector3 center = Vector3::ZERO;
};

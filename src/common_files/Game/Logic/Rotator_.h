// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Rotator : public LogicComponent
{
    URHO3D_OBJECT(Rotator, LogicComponent);
    
public:
    Rotator(Context* context);
    
    void SetRotationSpeed(const Vector3& speed);
    virtual void Update(float timeStep);

    static void RegisterComponent(Context *context = TheContext);
    
    const Vector3& GetRotationSpeed() const { return rotationSpeed; }
    
private:
    Vector3 rotationSpeed;
};

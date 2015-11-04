#pragma once


class Rotator : public ULogicComponent
{
    OBJECT(Rotator);
    
public:
    Rotator(UContext* context);
    
    void SetRotationSpeed(const Vector3& speed);
    virtual void Update(float timeStep);
    
    const Vector3& GetRotationSpeed() const { return rotationSpeed; }
    
private:
    Rotator& operator=(const Rotator&) {};
    Vector3 rotationSpeed;
};

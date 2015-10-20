#pragma once


class vRotator : public LogicComponent
{
    OBJECT(vRotator);
    
public:
    vRotator(Context* context);
    
    void SetRotationSpeed(const Vector3& speed);
    virtual void Update(float timeStep);
    
    const Vector3& GetRotationSpeed() const { return rotationSpeed; }
    
private:
    vRotator& operator=(const vRotator&) {};
    Vector3 rotationSpeed;
};

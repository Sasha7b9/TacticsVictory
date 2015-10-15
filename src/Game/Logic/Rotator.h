#pragma once


class tvRotator : public LogicComponent
{
    OBJECT(tvRotator);
    
public:
    tvRotator(Context* context);
    
    void SetRotationSpeed(const Vector3& speed);
    virtual void Update(float timeStep);
    
    const Vector3& GetRotationSpeed() const { return rotationSpeed; }
    
private:
    tvRotator& operator=(const tvRotator&) {};
    Vector3 rotationSpeed;
};

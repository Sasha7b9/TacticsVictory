 class TankUpdater : ScriptObject
 {
    Vector3 rotationSpeed;
    
    void SetRotationSpeed(const Vector3&in speed)
    {
        rotationSpeed = speed;
    }
    
    void Update(float timeStep)
    {
        node.Rotate(Quaternion(0.0f, rotationSpeed.y * timeStep, 0.0f));
    }
 }
 
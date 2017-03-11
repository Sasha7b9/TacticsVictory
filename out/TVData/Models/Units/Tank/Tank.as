 class TankUpdater : ScriptObject
 {
    Vector3 rotationSpeed;
	RocketLauncher@ launcher;
    
    void SetRotationSpeed(const Vector3&in speed, RocketLauncher@ launch)
    {
        rotationSpeed = speed;
		launcher = launch;
    }
    
    void Update(float timeStep)
    {
        node.Rotate(Quaternion(0.0f, rotationSpeed.y * timeStep, 0.0f));
		launcher.Update(timeStep);
    }
 }
 
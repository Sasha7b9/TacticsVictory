 class TankUpdater : ScriptObject
 {
    Vector3 rotationSpeed;
	RocketLauncher@ launcher;
	Translator@ translator;
    
    void SetRotationSpeed(const Vector3&in speed, RocketLauncher@ launch, Translator@ trans)
    {
        rotationSpeed = speed;
		launcher = launch;
		translator = trans;
    }
    
    void Update(float timeStep)
    {
        node.Rotate(Quaternion(0.0f, rotationSpeed.y * timeStep, 0.0f));
		launcher.Update(timeStep);
		if(!translator.IsMoving())
		{
		}
		else
		{
		}
    }
 }
 
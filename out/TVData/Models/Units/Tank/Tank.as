 class TankUpdater : ScriptObject
 {
	RocketLauncher@ launcher;
	Translator@ translator;
	Tank@ tank;
    
    void SetRotationSpeed(RocketLauncher@ launch, Translator@ trans, Tank@ tan)
    {
		launcher = launch;
		translator = trans;
		tank = tan;
	}
    
    void Update(float timeStep)
    {
		launcher.Update(timeStep);
		if(!translator.IsMoving())
		{
			if(tank.inProcessFindPath)
			{
				if(tank.pathFinder.PathIsFound())
				{
				}
			}
		}
		else
		{
		}
    }
 }
 
 class TankUpdater : ScriptObject
 {
	RocketLauncher@ launcher;
	Translator@ translator;
	Tank@ tank;
	WaveAlgorithm@ pathFinder;
    
    void SetRotationSpeed(RocketLauncher@ launch, Translator@ trans, Tank@ tan, WaveAlgorithm@ wave)
    {
		launcher = launch;
		translator = trans;
		tank = tan;
		pathFinder = wave;
	}
    
    void Update(float timeStep)
    {
		launcher.Update(timeStep);
		if(!translator.IsMoving())
		{
			if(tank.inProcessFindPath)
			{
			/*
				if(pathFinder.PathIsFound())
				{
				}
				*/
			}
		}
		else
		{
		}
    }
 }
 
 class TankUpdater : ScriptObject
 {
	RocketLauncher@ launcher;
	Translator@ translator;
	Tank@ tank;
	WaveAlgorithm@ pathFinder;
    
    void SetRotationSpeed(RocketLauncher@ launch, Translator@ trans, Tank@ tan)
    {
		launcher = launch;
		translator = trans;
		tank = tan;
	}
	
	void SetWaveAlgorithm(WaveAlgorithm@ wave)
	{
		pathFinder = wave;
	}
    
    void Update(float timeStep)
    {
		launcher.Update(timeStep);
		if(!translator.IsMoving())
		{
			if(tank.inProcessFindPath)
			{
				if(tank.PathIsFound())
				{
				}
			}
		}
		else
		{
		}
    }
 }
 
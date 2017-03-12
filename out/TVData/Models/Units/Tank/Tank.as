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
					Array<uint>@ pArr = tank.pathFinder.GetPathUINT();
					Array<uint> arr;
					for(uint i = 0; i < pArr.length; i++)
					{
						arr.Push(pArr[i]);
					}
				}
			}
		}
		else
		{
		}
    }
 }
 
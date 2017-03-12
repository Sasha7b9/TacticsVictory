 class TankUpdater : ScriptObject
 {
	RocketLauncher@ launcher;
	Translator@ translator;
	Tank@ tank;
//    Log log;
    
    void SetRotationSpeed(RocketLauncher@ launch, Translator@ trans, Tank@ tan)
    {
		launcher = launch;
		translator = trans;
		tank = tan;
//        log.Open("script.log");
	}
    
    void Update(float timeStep)
    {
		if(!translator.IsMoving())
		{
			if(tank.inProcessFindPath)
			{
				if(tank.pathFinder.PathIsFound())
				{
                    log.Write("                                                     4");
                    Array<uint> pArrU = tank.pathFinder.GetPathUINT();
                    for(uint i = 0; i < pArrU.length; i++)
                    {
                        log.Write("cicle");
                    }
                    /*
                    Array<uint> arrU;
					for(uint i = 0; i < pArrU.length; i++)
					{
						arrU.Push(pArrU[i]);
					}
                    for(uint i = 0; i < arrU.length; i++)
                    {
                     //   log.Write(String(i));
                    }
                    */
                    
                    /*
					const Array<String>@ pArr = tank.pathFinder.GetPathString();
                    
					Array<String> arr;
					for(uint i = 0; i < pArr.length; i++)
					{
						arr.Push(pArr[i]);
					}
                    */
                    //const Array<uint>@ pArrU = tank.pathFinder.GetPathUINT();
                    /*
                    */
    			}
			}
		}
		else
		{
		}
    }
 }
 
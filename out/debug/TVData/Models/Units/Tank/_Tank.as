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
        Array<String> args = GetArguments();
        log.Write("args");
        //log.Print(args.length);
        for(uint i = 0; i < args.length; i++)
        {
            log.Write(args[i]);
        }
        
        Array<String> strs = GetTestStrings();
        for(uint i = 0; i < strs.length; i++)
        {
            log.Write(strs[i]);
        }
	}
    
    void Update(float timeStep)
    {
		if(!translator.IsMoving())
		{
            /*
            Array<uint> arr = tank.pathFinder.GetPathUINT();
            if(arr.length == 0)
            {
                log.Write("array is Ok");
            }
            else
            {
                log.Write("array is ERROR!");
            }
            */
            
			if(tank.inProcessFindPath)
			{
				if(tank.pathFinder.PathIsFound())
				{
                    
                /*
                    Array<uint> pArrU = tank.pathFinder.GetPathUINT();
                    if(pArrU.length == 0)
                    {
                        log.Write("error pointer");
                    }
                    else
                    {
                        log.Write("nice work!");
                    }
                    */
                   
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
 
// 2021/12/17 0:00:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Staff/Commander_.h"
#include "Objects/Units/Unit_.h"
#include "Objects/Units/Air/AirUnit_.h"
#include "Objects/Units/Ground/GroundUnit_.h"
#include "Objects/Units/Water/WaterUnit_.h"
#include "Objects/Units/Air/Airplane_.h"
#include "Objects/Units/Air/Helicopter_.h"
#include "Objects/Units/Water/Boat_.h"
#include "Objects/Units/Ground/Robot_.h"
#include "Objects/Units/Ground/Tank_.h"
#include "Objects/Units/Ground/Worm.h"
#include "Objects/Units/Water/Submarine_.h"
#include "Objects/Staff/DriverTasks_.h"
#include "Objects/World/Landscape_.h"


using namespace Pi;


Commander::Commander(GameObject *_object) : object(*_object), driver(*_object->driver)
{
}


void Commander::Update(float dT)
{
#ifdef PiSERVER

    if (!tasks.Empty())
    {
        CommanderTask *task = tasks[0];

        task->RunStep(dT);

        if (task->Complete())
        {
            delete task;

            tasks.RemoveElement(0);
        }
    }

#endif
}


void Commander::AppendRandomTask()
{
    int value = 27;

    if ((rand() % value) == 0)
    {
        Point3D position = object.GetNodePosition();

        AppendTask(new CommanderTaskDive(&object, Math::RandomFloat(Landscape::self->GetHeightCenter(position.x, position.y), Water::Level())));
    }
    else if ((rand() % value) == 0)
    {
        AppendTask(new CommanderTaskRotate(&object, {0.0f, 0.0f, Math::RandomFloat(-K::pi, K::pi)}));
    }
    else if ((rand() % value) == 0)
    {
        Point3D position = object.GetNodePosition();

        int dX[4] = {0, 0,  1, -1};
        int dY[4] = {1, -1, 0, 0};

        int index = rand() % 4;

        AppendTask(new CommanderTaskMove(&object, position.x + (float)dX[index], position.y + (float)dY[index]));
    }
}

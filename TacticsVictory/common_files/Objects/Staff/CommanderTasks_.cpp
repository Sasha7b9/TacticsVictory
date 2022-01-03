// 2021/12/30 13:49:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Staff/CommanderTasks_.h"
#include "Objects/GameObject_.h"
#include "Objects/Staff/Driver_.h"
#include "Objects/Staff/DriverTasks_.h"


using namespace Pi;


CommanderTask::CommanderTask(GameObject *_object, Type _type, Mode _mode) :
    type(_type),
    mode(_mode),
    object(*_object),
    params(_object->params),
    driver(*_object->driver)
{ }


void CommanderTaskTest::RunStep(float dT)
{
#ifdef PiSERVER

    if (driver.NoCurrentTasks())
    {
        driver.AppendTask(new DriverTaskAlignDirection(&driver));
        if(driver.CanMoveForward())
        {
            driver.AppendTask(new DriverTaskMove(&driver, DriverTaskMove::Direction::Forward));
        }
        else
        {
            driver.AppendTask(new DriverTaskRotate(&driver, Vector3D::UP, -K::pi / 2.0f));
        }
    }
    else if (params.cur.velocity > 0.0f)
    {
        if (!driver.CanMoveForward())
        {
            driver.RemoveTasks();
            params.cur.velocity = 0.0f;
        }
    }

#endif
}

﻿// 2021/12/17 17:13:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/UnitParameters_.h"
#include "Objects/Units/Air/Airplane_.h"
#include "Objects/Units/Air/Helicopter_.h"
#include "Objects/Units/Ground/Robot_.h"
#include "Objects/Units/Ground/Tank_.h"
#include "Objects/Units/Ground/Worm.h"
#include "Objects/Units/Water/Boat_.h"
#include "Objects/Units/Water/Submarine_.h"


using namespace Pi;


const UnitParameters BoatController::parameters = UnitParameters
{
    {
        {0.0f, 0.05f, 0.0f},
        {0.0f, 0.0f, 0.05f}
    }
};


UnitParameters AirplaneController::parameters =
{
    {
        {0.05f, 0.5f, 0.05f},
        {0.05f, 0.05f, 0.05f}
    }
};


UnitParameters HelicopterController::parameters =
{
    {
        {0.25f, 0.25f, 0.25f},
        {0.001f, 0.01f, 0.05f}
    }
};


UnitParameters RobotController::parameters =
{
    {
        {0.0f, 0.2f, 0.0f},
        {0.0f, 0.0f, 0.05f}
    }
};


UnitParameters SubmarineController::parameters =
{
    {
        {0.0f, 0.3f, 0.005f},
        {0.01f, 0.0f, 0.001f}
    }
};


UnitParameters TankController::parameters =
{
    {
        {0.0f, 0.003f, 0.0f}
    }
};


UnitParameters WormController::parameters =
{
    {
        {0.0f, 0.1f, 0.0f}
    }
};
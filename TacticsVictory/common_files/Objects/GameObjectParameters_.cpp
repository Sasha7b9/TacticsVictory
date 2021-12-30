// 2021/12/17 17:13:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/GameObjectParameters_.h"
#include "Objects/Units/Air/Airplane_.h"
#include "Objects/Units/Air/Helicopter_.h"
#include "Objects/Units/Ground/Robot_.h"
#include "Objects/Units/Ground/Tank_.h"
#include "Objects/Units/Ground/Worm.h"
#include "Objects/Units/Water/Boat_.h"
#include "Objects/Units/Water/Submarine_.h"
#include "Objects/Weapons/Laser.h"
#include "Objects/Weapons/RocketLauncher.h"
#include "Objects/Structures/CivilianPlant_.h"
#include "Objects/Ammo/Bullet_.h"
#include "Objects/Ammo/Rocket_.h"
#include "Objects/Structures/ArmoryPlant_.h"


using namespace Pi;


const GameObjectParameters Boat::parameters =
{
    {
        {0.0f, 50.0f, 0.0f},        // speed
        {0.0f, 0.0f, 50.0f}         // rotate
    }
};


const GameObjectParameters Airplane::parameters =
{
    {
        {0.00f, 500.0f,  0.00f},      // speed
        {10.0f, 10.00f,  50.0f},      // rotate
        0.01f                         // accelerateSpeed
    }
};


const GameObjectParameters Helicopter::parameters =
{
    {
        {0.25f, 0.25f, 0.25f},
        {0.001f, 0.01f, 0.05f}
    }
};


const GameObjectParameters Robot::parameters =
{
    {
        {0.0f, 0.2f, 0.0f},
        {0.0f, 0.0f, 0.05f}
    }
};


const GameObjectParameters Submarine::parameters =
{
    {
        {0.0f, 0.3f, 0.005f},
        {0.01f, 0.0f, 0.001f}
    }
};


const GameObjectParameters Tank::parameters =
{
    {
        {0.0f, 3.0f, 0.0f}        // speed
    }
};


const GameObjectParameters Worm::parameters =
{
    {
        {0.0f, 0.1f, 0.0f}
    }
};


const GameObjectParameters Laser::parameters =
{

};


const GameObjectParameters RocketLauncher::parameters =
{

};


const GameObjectParameters CivilianPlant::parameters =
{

};


const GameObjectParameters Bullet::parameters =
{

};


const GameObjectParameters Rocket::parameters =
{

};


const GameObjectParameters ArmoryPlant::parameters =
{

};

// 2021/12/11 13:53:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    namespace PiTypeProperty
    {
        const S GameObject = "GameObject";
    }

    namespace TTypeGameObject
    {
        typedef StringHash S;

        const S Empty     = "Empty";
        const S Ammo      = "Ammo";
        const S Structure = "Structure";
        const S Unit      = "Unit";
        const S Weapon    = "Weapon";
    }

    namespace TTypeAmmo
    {
        typedef StringHash S;

        const S Bullet = "Bullet";
        const S Rocket = "Rocket";
    }

    namespace TTypeStructure
    {
        typedef StringHash S;

        const S ArmoryPlant   = "ArmoryPlant";
        const S CivilianPlant = "CivilianPlant";
    }

    namespace TTypeUnit
    {
        typedef StringHash S;

        const S Air         = "Air";
        const S Ground      = "Ground";
        const S Underground = "Underground";
        const S Water       = "Water";
    }

    namespace TTypeWeapon
    {
        typedef StringHash S;

        const S RocketLauncher = "RocketLauncher";
        const S Laser          = "Laser";
    }

    namespace TTypeAirUnit
    {
        typedef StringHash S;

        const S Airplane   = "Airplane";
        const S Helicopter = "Helicopter";
    }

    namespace TTypeGroundUnit
    {
        typedef StringHash S;

        const S Tank  = "Tank";
        const S Robot = "Robot";
        const S Worm  = "Worm";
    }

    namespace TTypeWaterUnit
    {
        typedef StringHash S;

        const S Submarine = "Submarine";
        const S Boat      = "Bot";
    }
}

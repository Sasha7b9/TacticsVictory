// 2021/12/11 13:53:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    namespace PiTypeProperty
    {
        const S GameObject = "GameObject";
    }

    namespace TypeGameObject
    {
        typedef StringHash S;

        const S Empty     = "Empty";
        const S Ammo      = "Ammo";
        const S Structure = "Structure";
        const S Unit      = "Unit";
        const S Weapon    = "Weapon";
    }

    namespace TypeAmmo
    {
        typedef StringHash S;

        const S Bullet = "Bullet";
        const S Rocket = "Rocket";
    }

    namespace TypeStructure
    {
        typedef StringHash S;

        const S ArmoryPlant   = "ArmoryPlant";
        const S CivilianPlant = "CivilianPlant";
    }

    enum class TypeUnit
    {
        Air,
        Ground,
        Underground,
        Water
    };

    namespace TypeWeapon
    {
        typedef StringHash S;

        const S RocketLauncher = "RocketLauncher";
        const S Laser          = "Laser";
    }

    namespace TypeAirUnit
    {
        typedef StringHash S;

        const S Airplane   = "Airplane";
        const S Helicopter = "Helicopter";
    }

    namespace TypeGroundUnit
    {
        typedef StringHash S;

        const S Robot = "Robot";
        const S Tank  = "Tank";
        const S Worm  = "Worm";
    }

    namespace TypeWaterUnit
    {
        typedef StringHash S;

        const S Boat      = "Bot";
        const S Submarine = "Submarine";
    }
}

// 2021/12/11 13:53:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    namespace PiTypeProperty
    {
        const S GameObject = "GameObject";
    }

    enum class TypeGameObject
    {
        Empty,
        Ammo,
        Structure,
        Unit,
        Weapon,
        World
    };

    enum class TypeAmmo
    {
        Bullet,
        Rocket
    };

    enum class TypeStructure
    {
        ArmoryPlant,
        CivilianPlant
    };

    enum class TypeUnit
    {
        None_,
        Air,
        Ground,
        Water
    };

    enum class TypeWeapon
    {
        RocketLauncher,
        Laser
    };

    enum class TypeAirUnit
    {
        Empty,
        Airplane,
        Helicopter
    };

    enum class TypeGroundUnit
    {
        Empty,
        Robot,
        Tank,
        Worm
    };

    enum class TypeWaterUnit
    {
        Empty,
        Boat,
        Submarine
    };

    enum class TypeWorldObject
    {
        Empty,
        Sun
    };
}

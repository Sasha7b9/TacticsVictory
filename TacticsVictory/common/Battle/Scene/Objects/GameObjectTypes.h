// 2021/12/11 13:53:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    namespace PiTypeProperty
    {
        const S GameObject = "GameObject";
    }

    namespace PiTypeGameObject
    {
        typedef StringHash S;

        const S Empty = "Empty";
        const S Unit  = "Unit";
    }

    namespace PiTypeUnitObject
    {
        typedef StringHash S;

        const S Ground = "Ground";
    }

    namespace PiTypeGroundUnitObject
    {
        typedef StringHash S;

        const S Tank = "Tank";
    }
}

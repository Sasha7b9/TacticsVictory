// 2021/02/25 22:14:38 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class TankSpecificC : public TankSpecific
{
    URHO3D_OBJECT(TankSpecificC, TankSpecific);

public:

    TankSpecificC(Tank *tank) : TankSpecific(tank) {}
};

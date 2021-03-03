// 2021/02/26 16:38:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class TankSpecificS : public TankSpecific
{
    URHO3D_OBJECT(TankSpecificS, TankSpecific);

public:

    TankSpecificS(Tank *tank) : TankSpecific(tank) {}

    virtual void Update(float timeStep) override;
};

// 2021/03/10 15:31:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class AirPlaneSpecificC : public UnitSpecificC
{
    URHO3D_OBJECT(AirPlaneSpecificC, UnitSpecificC);

public:

    AirPlaneSpecificC(AirPlane *airPlane) : UnitSpecificC(airPlane) {}

    virtual void Update(float dT) override;
};

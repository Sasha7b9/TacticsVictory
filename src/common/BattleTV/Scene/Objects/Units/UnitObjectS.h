// 2021/02/26 16:01:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Units/UnitObject_.h"


class UnitObjectSpecificS : public UnitObjectSpecific
{
    URHO3D_OBJECT(UnitObjectSpecificS, UnitObjectSpecific);

public:

    UnitObjectSpecificS(UnitObject *object) : UnitObjectSpecific(object) {}

protected:

    virtual void Update(float timeStep) override;
};


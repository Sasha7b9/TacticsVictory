// 2021/02/26 16:01:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/ObjectS.h"


class UnitSpecificS : public ObjectSpecificS
{
    URHO3D_OBJECT(UnitSpecificS, ObjectSpecificS);

public:

    UnitSpecificS(Unit *object) : ObjectSpecificS(object), unit(object) {}

protected:

    virtual void Update(float timeStep) override;

private:

    Unit *unit = nullptr;
};

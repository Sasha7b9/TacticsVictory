// 2021/02/23 11:06:07 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Ammo/TRocket_.h"


class CRocket : public Rocket
{
    URHO3D_OBJECT(CRocket, Rocket);

public:

    static SharedPtr<CRocket> Create();

private:

    CRocket(Context *context);
};

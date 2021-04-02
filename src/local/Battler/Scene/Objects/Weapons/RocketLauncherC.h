// 2021/02/22 21:19:41 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Weapons/RocketLauncher_.h"


class CRocketLauncher : public RocketLauncher
{
    URHO3D_OBJECT(CRocketLauncher, RocketLauncher);

public:

    static SharedPtr<CRocketLauncher> Create();

private:

    CRocketLauncher(Context *context);
};

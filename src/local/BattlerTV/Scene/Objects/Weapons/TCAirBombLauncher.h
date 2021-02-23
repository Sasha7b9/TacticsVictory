// 2021/02/23 11:30:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Weapons/_TAirBombLauncher.h"
#include "Scene/Objects/Weapons/TCWeaponObject.h"


class CAirBombLauncher : public AirBombLauncher, public CWeaponObject
{
    URHO3D_OBJECT(CAirBombLauncher, AirBombLauncher);

public:

    static SharedPtr<CAirBombLauncher> Create();

private:

    CAirBombLauncher();
};

// 2021/02/22 21:32:46 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Weapons/_TGrenadeLauncher.h"


class CGrenadeLauncher : public GrenadeLauncher
{
    URHO3D_OBJECT(CGrenadeLauncher, GrenadeLauncher);

public:

    static SharedPtr<CGrenadeLauncher> Create();

private:

    CGrenadeLauncher();
};

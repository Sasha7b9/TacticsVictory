// 2021/02/22 15:46:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/TGameObject_.h"


class UnitObject : public GameObject
{
    URHO3D_OBJECT(UnitObject, GameObject);

protected:

    UnitObject(Context *context);

    virtual void Start() override;

    static Vector<UnitObject *> storage;
};

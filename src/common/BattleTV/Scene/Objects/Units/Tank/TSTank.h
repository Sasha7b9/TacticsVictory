// 2021/02/17 15:55:34 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/Units/Tank/_TTank.h"


class STank : public Tank
{
    URHO3D_OBJECT(STank, Tank);

public:

    STank(Context *context) : Tank(context) {}

    static void RegisterObject(Context *context = TheContext);

    static void RegisterInAS();

    static SharedPtr<STank> Create(Tank::TypeTank type, uint _id_ = 0);

    virtual void Existor() override {}
};



// 2021/02/17 15:45:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/Units/Tank/_TTank.h"


class WaveAlgorithm;


class CTank : public Tank
{
    URHO3D_OBJECT(CTank, Tank);

public:

    CTank(Context *context) : Tank(context) { }

    static void RegisterObject(Context *context = TheContext);

    static void RegisterInAS();

    virtual void Update(float dT) override;

    static SharedPtr<CTank> Create(Tank::Type::E type, uint _id_ = 0);

    virtual void Existor() override {}

private:
    SharedPtr<WaveAlgorithm> pathFinder;

    virtual void Init(Tank::Type::E typeTank, uint _id_) override;
};

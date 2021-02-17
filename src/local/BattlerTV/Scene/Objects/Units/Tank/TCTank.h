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

    virtual void Existor() override {}

    static void RegisterInAS();

    virtual void Update(float dT) override;

    static SharedPtr<CTank> Create(TypeTank type, uint _id_ = 0);

private:
    SharedPtr<WaveAlgorithm> pathFinder;

    virtual void Init(TypeTank typeTank, uint _id_) override;
};

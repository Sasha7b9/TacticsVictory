// 2021/02/22 20:45:07 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Units/Unit_.h"


class AirPlane : public Unit
{
    URHO3D_OBJECT(AirPlane, Unit);

public:

    AirPlane(Context *);

    static void RegisterComponent();

    virtual void CreateSpecific() override;

    static Vector<AirPlane *> storage;

    virtual void Compress(VectorBuffer &buffer) override;

    virtual void Decompress(MemoryBuffer &buffer) override;

private:

    virtual void OnNodeSet(Node *node) override;

    virtual void Start() override;

    virtual void Update(float dT) override;
};

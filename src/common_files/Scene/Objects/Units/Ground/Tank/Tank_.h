// 2021/02/22 15:41:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/PhysicsParameters_.h"
#include "Scene/Objects/Units/Ground/GroundUnit_.h"


//----------------------------------------------------------------------------------------------------------------------
class Tank : public GroundUnit
{
    URHO3D_OBJECT(Tank, GroundUnit);

public:

    Tank(Context *);

    static void RegisterComponent();

    virtual void CreateSpecific() override;

    virtual void Compress(VectorBuffer &buffer) override;

    virtual void Decompress(MemoryBuffer &buffer) override;

    static Vector<Tank *> storage;              // Хранилище всех созданных объектов типа "Tank"

private:

    // Во время создания компонента после помещения его на ноду вызывается эта функция
    virtual void OnNodeSet(Node *node) override;

    // Эта функция вызывается из NodeSet
    virtual void Start() override;

    virtual void Update(float dT) override;
};

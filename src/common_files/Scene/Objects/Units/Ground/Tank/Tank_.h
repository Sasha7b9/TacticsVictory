// 2021/02/22 15:41:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/Units/UnitObject_.h"


class Tank;


//----------------------------------------------------------------------------------------------------------------------
class TankSpecific : public UnitObjectSpecific
{
    URHO3D_OBJECT(TankSpecific, UnitObjectSpecific);

public:

    TankSpecific(Tank *tank);

    virtual void Update(float timeStep);
};


//----------------------------------------------------------------------------------------------------------------------
class Tank : public UnitObject
{
    URHO3D_OBJECT(Tank, UnitObject);

public:

    Tank(Context *);

    static void RegisterObject();

    // Хранилище всех созданных объектов типа "Tank"
    static Vector<Tank *> storage;

private:

    // Во время создания компонента после помещения его на ноду вызывается эта функция
    virtual void OnNodeSet(Node *node) override;

    // Эта функция вызывается из NodeSet
    virtual void Start() override;

    virtual void Update(float time) override;
};

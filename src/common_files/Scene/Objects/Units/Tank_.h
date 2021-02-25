// 2021/02/22 15:41:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/Units/UnitObject_.h"


class Tank;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TankSpecificPart : public Object
{
    URHO3D_OBJECT(TankSpecificPart, Object);

public:

    TankSpecificPart() : Object(TheContext) {};

    // Функция вызывается из функции Tank::Start() для выполнения специфичных действий
    virtual void Start(Tank *_tank) { tank = _tank; };

protected:

    Tank *tank = nullptr;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Tank : public UnitObject
{
friend class TankSpecificPartC;

    URHO3D_OBJECT(Tank, UnitObject);

public:

    Tank(Context *context);

    static void RegisterObject();

private:

    // Во время создания компонента после помещения его на ноду вызывается эта функция
    virtual void OnNodeSet(Node *node) override;

    // Эта функция вызывается из NodeSet
    virtual void Start() override;

    virtual void FixedUpdate(float time) override;

    // Хранилище всех созданных объектов типа "Tank"
    static Vector<Tank *> storage;

    SharedPtr<TankSpecificPart> specific;
};

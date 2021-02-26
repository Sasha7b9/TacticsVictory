// 2021/02/22 15:41:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/Units/UnitObject_.h"


class Tank;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TankSpecificPart : public Component
{
    URHO3D_OBJECT(TankSpecificPart, Component);

public:

    TankSpecificPart(Context *context) : Component(context) {};

    virtual void OnNodeSet(Node *node) override;

    // Создаёт на заданной ноде специфичный для данной среды (сервер/клиент) объект
    static void Create(Node *);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Tank : public UnitObject
{
friend class TankSpecificPartC;

    URHO3D_OBJECT(Tank, UnitObject);

public:

    Tank(Context *);

    static void RegisterObject();

private:

    // Во время создания компонента после помещения его на ноду вызывается эта функция
    virtual void OnNodeSet(Node *node) override;

    // Эта функция вызывается из NodeSet
    virtual void Start() override;

    virtual void FixedUpdate(float time) override;

    // Хранилище всех созданных объектов типа "Tank"
    static Vector<Tank *> storage;
};

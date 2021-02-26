// 2021/02/22 15:41:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/Units/UnitObject/UnitObject_.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TankSpecific : public Component
{
public:

    TankSpecific(Context *context) : Component(context) {};

    // Создаёт на заданной ноде специфичный для данной среды (сервер/клиент) объект
    static void CreateSpecific(Node *);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Tank : public UnitObject
{
public:

    Tank(Context *);

    static void RegisterObject();

    // Хранилище всех созданных объектов типа "Tank"
    static Vector<Tank *> storage;

    virtual void Update(float timeStep) override;

private:

    // Во время создания компонента после помещения его на ноду вызывается эта функция
    virtual void OnNodeSet(Node *node) override;

    // Эта функция вызывается из NodeSet
    virtual void Start() override;

    virtual void FixedUpdate(float time) override;
};

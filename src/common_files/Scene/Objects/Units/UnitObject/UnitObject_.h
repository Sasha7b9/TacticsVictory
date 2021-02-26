// 2021/02/22 15:46:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/GameObject_.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UnitObjectSpecificPart : public Component
{
public:

    UnitObjectSpecificPart(Context *context) : Component(context) {}

    static void Create(Node *);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UnitObject : public GameObject
{
protected:

    UnitObject(Context *);

    virtual void Start() override;

    static Vector<UnitObject *> storage;
};

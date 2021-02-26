// 2021/02/22 15:46:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/GameObject_.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UnitObjectSpecific : public Component
{
public:

    UnitObjectSpecific(Context *context) : Component(context) {}

//    static void CreateSpecific(Node *);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UnitObject : public GameObject
{
public:

    static Vector<UnitObject *> storage;

protected:

    UnitObject(Context *);

    virtual void Start() override;
};

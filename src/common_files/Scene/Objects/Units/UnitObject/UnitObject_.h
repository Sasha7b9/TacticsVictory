// 2021/02/22 15:46:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/GameObject_.h"
#include "Scene/Objects/Units/Accessories/Engine/Engine_.h"


//----------------------------------------------------------------------------------------------------------------------
class UnitObjectSpecific : public Component
{
    URHO3D_OBJECT(UnitObjectSpecific, Component);

public:

    UnitObjectSpecific(Context *context) : Component(context) {}

    static void RegisterObject();

    static void CreateSpecific(Node *node);
};


//----------------------------------------------------------------------------------------------------------------------
class UnitObject : public GameObject
{
    URHO3D_OBJECT(UnitObject, GameObject);

public:

    static Vector<UnitObject *> storage;

    static void RegisterObject();

    virtual void Update(float timeStep);

protected:

    UnitObject(Context *);

    virtual void Start() override;
};

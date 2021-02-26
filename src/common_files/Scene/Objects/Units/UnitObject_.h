// 2021/02/22 15:46:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/GameObject_.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UnitObjectSpecificPart : public Object
{
    URHO3D_OBJECT(UnitObjectSpecificPart, Object);

public:

    UnitObjectSpecificPart() : Object(TheContext) {}

    static void Create(Node *);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UnitObject : public GameObject
{
    URHO3D_OBJECT(UnitObject, GameObject);

protected:

    UnitObject(UnitObjectSpecificPart *specific);

    virtual void Start() override;

    static Vector<UnitObject *> storage;

    SharedPtr<UnitObjectSpecificPart> specificUnity;
};

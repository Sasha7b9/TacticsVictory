// 2021/02/22 15:46:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/GameObject_.h"
#include "Scene/Objects/Units/Accessories/Engine/Engine_.h"


class UnitObject;


//----------------------------------------------------------------------------------------------------------------------
class UnitObjectSpecific : public GameObjectSpecific
{
    URHO3D_OBJECT(UnitObjectSpecific, GameObjectSpecific);

public:

    UnitObjectSpecific(UnitObject *object);

    static UnitObjectSpecific *Create(UnitObject *object);

    virtual void Update(float timeStep) override;
};


//----------------------------------------------------------------------------------------------------------------------
class UnitObject : public GameObject
{
    URHO3D_OBJECT(UnitObject, GameObject);

public:

    static Vector<UnitObject *> storage;

    virtual void Update(float timeStep) override;

protected:

    UnitObject(Context *);

    virtual void Start() override;

    SharedPtr<EngineT> engine;
};

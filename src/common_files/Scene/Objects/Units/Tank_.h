// 2021/02/22 15:41:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/Units/UnitObject_.h"


class TankSpecificPart : public Object
{
    URHO3D_OBJECT(TankSpecificPart, Object);

public:

    TankSpecificPart();

    virtual void Start(Node *) {};

    virtual void OnMouseClick(VariantMap &, Node *) { };
};


class Tank : public UnitObject
{
friend class TankSpecificPartC;

    URHO3D_OBJECT(Tank, UnitObject);

public:

    Tank(Context *context);

    static void RegisterObject();

private:

    virtual void OnNodeSet(Node *node) override;

    virtual void Start() override;

    virtual void FixedUpdate(float time) override;

    static Vector<Tank *> storage;

    void HandleMouseClick(StringHash, VariantMap &);

    SharedPtr<TankSpecificPart> specific;
};

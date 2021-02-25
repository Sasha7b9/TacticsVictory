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

    virtual void Start(Node *_node, Tank *_tank) { node = _node; tank = _tank; };

    virtual void OnMouseClick(VariantMap &) { };

protected:

    Node *node = nullptr;
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

    virtual void OnNodeSet(Node *node) override;

    virtual void Start() override;

    virtual void FixedUpdate(float time) override;

    static Vector<Tank *> storage;

    void HandleMouseClick(StringHash, VariantMap &);

    SharedPtr<TankSpecificPart> specific;
};

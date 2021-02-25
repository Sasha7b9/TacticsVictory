// 2021/02/22 15:41:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/Units/TankSpecificPart_.h"
#include "Scene/Objects/Units/UnitObject_.h"


class StatusBar;


class Tank : public UnitObject
{
    URHO3D_OBJECT(Tank, UnitObject);

public:

    Tank(Context *context);

    static void RegisterObject();

private:

    virtual void OnNodeSet(Node *node) override;

    virtual void Start() override;

    virtual void FixedUpdate(float time) override;

    static Vector<Tank *> storage;

    SharedPtr<Tile> tile;

    void HandleMouseClick(StringHash, VariantMap &);

    SharedPtr<TankSpecificPart> specific;
};

// 2021/02/26 15:53:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Graphics/3D/TileSelected.h"
#include "Scene/Objects/ObjectC.h"


class UnitObjectSpecificC : public ObjectSpecificC
{
    URHO3D_OBJECT(UnitObjectSpecificC, ObjectSpecificC);

public:

    UnitObjectSpecificC(Unit *object);

    SharedPtr<TileSelected> tile;

    virtual void Update(float timeStep) override;

    virtual void HandleMouseClick(StringHash, VariantMap &);
};

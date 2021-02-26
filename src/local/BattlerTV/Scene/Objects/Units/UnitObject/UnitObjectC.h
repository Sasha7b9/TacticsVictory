// 2021/02/26 15:53:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Graphics/3D/TileSelected.h"
#include "Scene/Objects/Units/UnitObject/UnitObject_.h"


class UnitObjectSpecificC : public UnitObjectSpecific
{
public:

    UnitObjectSpecificC(Context *context) : UnitObjectSpecific(context) {}

    virtual void OnNodeSet(Node *node) override;

    SharedPtr<TileSelected> tile;

    void HandleMouseClick(StringHash, VariantMap &);
};

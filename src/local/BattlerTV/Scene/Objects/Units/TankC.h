// 2021/02/25 22:14:38 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Graphics/3D/TileSelected.h"


class TankSpecificPartC : public TankSpecificPart
{
public:

    virtual void Start(Tank *tank) override;

    SharedPtr<TileSelected> tile;

    void HandleMouseClick(StringHash, VariantMap &);
};

// 2021/02/25 21:34:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Graphics/3D/TTile.h"
#include "Scene/Objects/Units/Tank_.h"


class TankSpecificPartC : public TankSpecificPart
{
public:

    virtual void Start(Node *node) override;

    SharedPtr<Tile> tile;

    virtual void OnMouseClick(VariantMap &eventData, Node *node) override;
};

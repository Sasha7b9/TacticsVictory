// 2021/02/26 14:10:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Graphics/3D/Tile.h"


class TileSelected : public Tile
{
    URHO3D_OBJECT(TileSelected, Tile);

public:

    TileSelected(Context *context);

    static void RegisterComponent();

private:

    virtual ~TileSelected();
};

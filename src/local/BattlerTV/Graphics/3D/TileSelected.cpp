// 2021/02/26 14:11:02 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Graphics/3D/TileSelected.h"


TileSelected::TileSelected(Context *context) : Tile(context)
{
    shiftPosition = { 0.5f, 0.0f, -0.5f };
}


TileSelected::~TileSelected()
{

}


void TileSelected::RegisterComponent()
{
    TheContext->RegisterFactory<TileSelected>();
}

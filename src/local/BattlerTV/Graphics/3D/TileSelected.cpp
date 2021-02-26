// 2021/02/26 14:11:02 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Graphics/3D/TileSelected.h"


TileSelected::TileSelected(Context *context) : Tile(context)
{

}


TileSelected::~TileSelected()
{

}


void TileSelected::RegisterObject()
{
    TheContext->RegisterFactory<TileSelected>();
}

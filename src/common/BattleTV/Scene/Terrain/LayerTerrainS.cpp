// 2021/02/27 18:48:41 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Scene_.h"
#include "Scene/Terrain/LayerTerrain_.h"


Node *LayerTerrain::CreateChild()
{
    return TheScene->CreateChild(NAME_NODE_TERRAIN);
}

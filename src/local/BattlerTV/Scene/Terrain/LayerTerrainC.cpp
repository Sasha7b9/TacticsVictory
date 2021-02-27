// 2021/02/27 18:44:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/SceneC.h"
#include "Scene/Terrain/LayerTerrain_.h"


Node *LayerTerrain::CreateChild()
{
    return TheScene->CreateChild(NAME_NODE_TERRAIN);
}
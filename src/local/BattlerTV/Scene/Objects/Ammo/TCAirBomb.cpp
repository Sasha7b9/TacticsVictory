// 2021/02/23 11:39:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/TCScene.h"
#include "Scene/Objects/Ammo/TCAirBomb.h"


CAirBomb::CAirBomb(Context *context) : AirBomb(context)
{

}


SharedPtr<CAirBomb> CAirBomb::Create()
{
    SharedPtr<Node> node(TheScene->CreateChild("CAirBomb"));
    SharedPtr<CAirBomb> bomb(node->CreateComponent<CAirBomb>());

    return bomb;
}

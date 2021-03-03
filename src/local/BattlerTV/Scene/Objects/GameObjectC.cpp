// 2021/02/26 16:25:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/GameObject_.h"
#include "Scene/Objects/GameObjectC.h"


GameObjectSpecific *GameObjectSpecific::Create(GameObject *object)
{
    return new GameObjectSpecificC(object);
}


GameObjectSpecificC::GameObjectSpecificC(GameObject *object) : GameObjectSpecific(object)
{

}

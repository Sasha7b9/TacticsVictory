// 2021/02/26 16:25:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Object_.h"
#include "Scene/Objects/ObjectC.h"


ObjectSpecific *ObjectSpecific::Create(ObjectT *object)
{
    return new GameObjectSpecificC(object);
}


GameObjectSpecificC::GameObjectSpecificC(ObjectT *object) : ObjectSpecific(object)
{

}

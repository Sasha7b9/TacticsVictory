// 2021/02/17 13:13:02 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/SceneC.h"


SceneC::SceneC(SceneC **self) : SceneT()
{
    *self = this;
}


SceneC::~SceneC()
{

}


void SceneC::Create()
{
    SceneT::Create();
}

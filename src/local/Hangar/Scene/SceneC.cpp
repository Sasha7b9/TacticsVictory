// 2021/02/17 13:13:02 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/SceneC.h"


SceneC::SceneC(SceneC **self) : Scene(TheContext)
{
    *self = this;
}


SceneC::~SceneC()
{

}


void SceneC::Create()
{
}

// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Core/Math_.h"
#include "Game/Logic/SunEngine_.h"
#include "Scene/Level_.h"
#include "Scene/Scene_.h"


SceneT::SceneT(Context *context) : Scene(context)
{

}


SceneT::~SceneT()
{
    delete TheTerrain;
}


void SceneT::RegisterObject(Context *context)
{
    context->RegisterFactory<SceneT>();
}

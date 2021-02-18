// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "TBattle.h"
#include "Scene/_TScene.h"
#include "Scene/Objects/Ammo/Rocket/_TRocket.h"


void Battle::HandleUpdate(StringHash, VariantMap& eventData) //-V2009
{
    float time = eventData[Update::P_TIMESTEP].GetFloat();

    if (scene)
    {
        scene->Update(time);
    }
}


void Battle::HandlePostUpdate(StringHash, VariantMap& eventData) //-V2009
{
    float time = eventData[Update::P_TIMESTEP].GetFloat();

    Rocket::UpdateAll(time);
}

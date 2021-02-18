﻿// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "TBattle.h"
#include "Scene/_TScene.h"


void Battle::HandleUpdate(StringHash, VariantMap& eventData)
{
    float time = eventData[Update::P_TIMESTEP].GetFloat();

    if (scene)
    {
        scene->Update(time);
    }
}


void Battle::HandlePostUpdate(StringHash, VariantMap& eventData)
{
    UNUSED(eventData);
}

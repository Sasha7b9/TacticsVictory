// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


void Battle::HandleUpdate(StringHash, VariantMap& eventData) //-V2009
{
    float time = eventData[Update::P_TIMESTEP].GetFloat();

#ifdef CLIENT

    TheCamera->Move(time);

    if (TheCursor)
    {
        TheCursor->Update(time);
    }

#endif

#ifdef SERVER

    if (scene)
    {
        scene->Update(time);
    }

#endif
}


void Battle::HandlePostUpdate(StringHash, VariantMap& eventData) //-V2009
{
    float time = eventData[Update::P_TIMESTEP].GetFloat();

    Rocket::UpdateAll(time);
}

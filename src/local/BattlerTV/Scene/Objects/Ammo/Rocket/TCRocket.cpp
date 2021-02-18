#include "stdafx.h"
#include "Audio/TSounds.h"
#include "Game/TParticles.h"
#include "Scene/Objects/Ammo/Rocket/TCRocket.h"


void CRocket::SetParameters(float timeStep)
{
    Rocket::SetParameters(timeStep);

    if (collisionWithTerrain || (time > rangeTime))
    {
        Sounds::Play(Sound_Explosion, position);
        Particles::EmittingStatic(Explosion_Terrain, node_->GetPosition());
    }
    else if (attackedUnit)
    {
        Sounds::Play(Sound_Explosion, position);
    }
}

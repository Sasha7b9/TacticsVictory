// 2021/12/28 21:02:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Graphics/Effects/SmokeTrail.h"


using namespace Pi;


SmokeTrailParticleSystem::SmokeTrailParticleSystem() :
    PointParticleSystem(PiTypeParticleSystem::SmokeTrail, &particlePool, "texture/Trail"),
    particlePool(MaxParticles, particleArray)
{
}


SmokeTrailParticleSystem::SmokeTrailParticleSystem(const ColorRGBA &color) :
    PointParticleSystem(PiTypeParticleSystem::SmokeTrail, &particlePool, "texture/Trail"),
    particlePool(MaxParticles, particleArray)
{
    smokeColor = color;
}


void SmokeTrailParticleSystem::Preprocess()
{
    SetParticleSystemFlags(PiFlagParticleSystem::SoftDepth | PiFlagParticleSystem::DepthRamp);
    PointParticleSystem::Preprocess();

    SetAmbientBlendState(BlendState::Interpolate);

    SetSoftDepthScale(2.0F);
    SetDepthRampRange(Range<float>(0.125F, 1.0F));
}


void SmokeTrailParticleSystem::AnimateParticles()
{
    int dt = TheTimeMgr->GetDeltaTime();

    int counter = 0;

    Particle *particle = GetFirstParticle();
    while (particle)
    {
        counter++;
        Particle *next = particle->nextParticle;

        int life = (particle->lifeTime -= dt);

        particle->radius += (float)dt / 100000.0f;

        if (life <= 0)
        {
            FreeParticle(particle);
        }

        particle = next;
    }
}


void SmokeTrailParticleSystem::CreateSmoke(const Point3D &position, int life, float radius)
{
    Particle *particle = particlePool.NewParticle();
    if (particle)
    {
        particle->emitTime = 0;
        particle->lifeTime = life;
        particle->radius = radius;
        particle->color = smokeColor;
        particle->orientation = Math::Random(256) << 24;
        particle->position = position;

        AddFarthestParticle(particle);
    }
}

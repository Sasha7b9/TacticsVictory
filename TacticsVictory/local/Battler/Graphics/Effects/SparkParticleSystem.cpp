// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Graphics/Effects/SparkParticleSystem.h"


using namespace Pi;


SparkParticleSystem::SparkParticleSystem(int count)
    : LineParticleSystem(PiTypeParticleSystem::Spark, &particlePool, "particle/Spark1")
{

    sparkCount = count;
    SetLengthMultiplier(4.0F);
    SetParticleSystemFlags(PiFlagParticleSystem::SelfDestruct);
}

SparkParticleSystem::SparkParticleSystem()
    : LineParticleSystem(PiTypeParticleSystem::Spark, &particlePool, "particle/Spark1")
{
}

SparkParticleSystem::~SparkParticleSystem()
{
}

bool SparkParticleSystem::CalculateBoundingSphere(BoundingSphere *sphere) const
{
    sphere->SetCenter(0.0F, 0.0F, 0.0F);
    sphere->SetRadius(20.0F);
    return (true);
}

void SparkParticleSystem::Preprocess()
{
    LineParticleSystem::Preprocess();
    if (!GetFirstParticle())
    {
        Point3D center = GetSuperNode()->GetWorldTransform() * GetNodePosition();
        const ConstVector2D *trig = Math::GetTrigTable();
        int count = sparkCount;
        for (machine a = 0; a < count; a++)
        {
            Particle *particle = particlePool.NewParticle();
            if (!particle)
            {
                break;
            }
            particle->emitTime = 0;                         // Particle appears right away.
            particle->lifeTime = (int)(500 + Math::Random(750));// Particle lives 500-1250 milliseconds.
            particle->radius = 0.02F;                       // The radius is 20 mm.
            particle->color.Set(1.0F, 1.0F, 0.1F, 1.0F);	    // It's yellow.
            particle->orientation = 0;                      // This doesn't matter for line particles.
            particle->position = center;	                    // It starts at the effect's center.
            float speed = Math::RandomFloat(0.004F);
            Vector2D csp = trig[Math::Random(128)] * speed;
            const Vector2D &cst = trig[Math::Random(256)];
            particle->velocity.Set(cst.x * csp.y, cst.y * csp.y, csp.x);
            AddParticle(particle);
        }
    }
}

void SparkParticleSystem::AnimateParticles()
{
    int dt = TheTimeMgr->GetDeltaTime();
    float fdt = TheTimeMgr->GetFloatDeltaTime();
    Particle *particle = GetFirstParticle();
    while (particle)
    {
        Particle *next = particle->nextParticle;
        int life = (particle->lifeTime -= dt);
        if (life > 0)
        {
            particle->velocity.z += K::gravity * fdt;
            float z1 = particle->position.z - particle->radius;
            particle->position += particle->velocity * fdt;
            float z2 = particle->position.z - particle->radius;
            if (z1 * z2 <= 0.0F)
            {
                particle->position.z = 0.05F - z2;
                particle->velocity.z *= -0.5F;
            }
            if (life < 100)
            {
                particle->color.alpha = (float)life * 0.01F;
            }
        }
        else
        {
            FreeParticle(particle);
        }

        particle = next;
    }
}
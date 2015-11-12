#pragma once


enum TypeParticles
{
    Particle_Explosion,
    NumParticles
};


class Particles
{
public:
    static void Init();
    static void Emitting(TypeParticles type, const Vector3 position);

private:
    static Vector<Vector<ParticleEmitter*>> particles;
};
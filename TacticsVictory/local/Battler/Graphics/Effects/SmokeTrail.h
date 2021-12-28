// 2021/12/28 21:01:40 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    namespace PiTypeParticleSystem
    {
        const S SmokeTrail = "SmokeTrail";
    }


    class SmokeTrailParticleSystem : public PointParticleSystem
    {
        friend class Game;

    private:

        enum : uint
        {
            MaxParticles = 100000
        };

        ColorRGBA       smokeColor;

        ParticlePool<>  particlePool;
        Particle        particleArray[MaxParticles];

        SmokeTrailParticleSystem();

    public:

        SmokeTrailParticleSystem(const ColorRGBA &color);
        ~SmokeTrailParticleSystem() {};

        void Finalize()
        {
            SetParticleSystemFlags(GetParticleSystemFlags() | PiFlagParticleSystem::SelfDestruct);
        }

        void Preprocess() override;
        void AnimateParticles() override;

        void CreateSmoke(const Point3D &position, int life, float radius);
    };
}

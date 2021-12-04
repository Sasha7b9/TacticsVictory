// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{

    namespace PiTypeParticleSystem
    {
        const S Spark = 'sprk';
    }
    
    class SparkParticleSystem : public LineParticleSystem
    {
    
        friend class ParticleSystemReg<SparkParticleSystem>;
    
    public:
        SparkParticleSystem(int count);
        ~SparkParticleSystem();
    
        void Preprocess() override;
        void AnimateParticles() override;
    
    private:
        enum
        {
            kMaxParticleCount = 100
        };
    
        SparkParticleSystem();
    
        int				    sparkCount = 0;
        Particle			particleArray[kMaxParticleCount] {};
        ParticlePool<>		particlePool{kMaxParticleCount, particleArray};
        bool CalculateBoundingSphere(BoundingSphere *sphere) const override;
    };

}

// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    enum
    {
        kMovePanel,
        kNumSounds
    };

    class SoundPlayer : public Singleton<SoundPlayer>
    {
    public:
        static void Create();
        virtual ~SoundPlayer();
        static SoundPlayer *self;
        void Play(uint number);
    private:
        SoundPlayer();
        pchar sounds[kNumSounds];
    };
}

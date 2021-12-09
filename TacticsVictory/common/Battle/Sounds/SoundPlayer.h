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
        SoundPlayer();
        ~SoundPlayer();

        static SoundPlayer *self;

        void Play(uint number);

    private:
        pchar sounds[kNumSounds];
    };
}

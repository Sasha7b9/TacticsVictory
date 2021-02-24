// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


enum SoundType
{
    Sound_Explosion
};


class Sounds
{
public:
    static void Init();
    static void Play(SoundType type, const Vector3 &position);

private:
    static VariantMap sounds;
};

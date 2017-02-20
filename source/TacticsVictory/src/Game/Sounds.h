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
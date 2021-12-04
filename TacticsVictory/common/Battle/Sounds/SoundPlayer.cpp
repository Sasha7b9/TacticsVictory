// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "SoundPlayer.h"


using namespace Pi;


SoundPlayer::SoundPlayer() : Singleton<SoundPlayer>(TheSoundPlayer)
{
     sounds[kMovePanel] = "sounds/shoot";
}

SoundPlayer::~SoundPlayer()
{
}

void SoundPlayer::Play(uint number)
{
    Sound *sound = new Sound();
    sound->Load(sounds[number]);
    sound->Play();
} //-V773
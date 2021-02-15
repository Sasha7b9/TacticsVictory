/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include <stdafx.h>
#include "Sounds.h"


VariantMap Sounds::sounds;
PODVector<SoundSource3D*> sources;



void Sounds::Init()
{
    sounds[StringHash(Sound_Explosion)] = TheCache->GetResource<Sound>("Sounds/ExplosionMissile.wav");
    Node *nodeSource = TheScene->CreateChild("Sound");
    SoundSource3D* soundSource = nodeSource->CreateComponent<SoundSource3D>();
    soundSource->SetDistanceAttenuation(1.0f, 5.0f, 0.01f);
    soundSource->SetSoundType(SOUND_EFFECT);
    sources.Push(soundSource);
}


void Sounds::Play(SoundType type, const Vector3 &position)
{
    SoundSource3D *source = nullptr;
    for (auto src : sources)
    {
        if (!src->IsPlaying())
        {
            source = src;
            break;
        }
    }
    
    if (!source)
    {
        Node *nodeSource = TheScene->CreateChild("Sound");
        source = (SoundSource3D*)nodeSource->CloneComponent(sources[0]);
        sources.Push(source);
    }

    source->GetNode()->SetPosition(position);
    source->Play((Sound*)sounds[StringHash((uint)type)].GetPtr());
}

#include <stdafx.h>


#include "Particles.h"


Vector<Vector<ParticleEmitter*>> Particles::particles;


void Particles::Init()
{
    for (uint i = 0; i < NumParticles; i++)
    {
        particles.Push(Vector<ParticleEmitter*>());
    }

    Node *node = gScene->CreateChild("Emitter");
    node->SetScale(5.0f);
    ParticleEmitter *emitter = node->CreateComponent<ParticleEmitter>();
    emitter->SetViewMask(VIEW_MASK_FOR_EFFECTS);
    /*
    XMLFile xmlParticle = XMLFile(gContext);
    SharedPtr<File> file(gCache->GetFile("Particle/SnowExplosion.xml"));
    if (file)
    {
        xmlParticle.Load(*file);
        SharedPtr<ParticleEffect> pe(new ParticleEffect(gContext));
        XMLElement root = xmlParticle.GetRoot("particleemitter");
        pe->Load(root);
        emitter->SetEffect(pe);
        emitter->SetEmitting(false);
        Vector<ParticleEmitter*> &emitters = particles.At(Particle_Explosion);
        emitters.Push(emitter);
    }
    */
}

void Particles::Emitting(TypeParticles /*type*/, const Vector3 /*position*/)
{
    /*
    ParticleEmitter* emitter = nullptr;
    
    Vector<ParticleEmitter*> &emitters = particles.At(type);

    for (auto em : emitters)
    {
        if (!em->IsEmitting())
        {
            emitter = em;
            break;
        }
    }

    if (!emitter)
    {
        Node *node = gScene->CreateChild("Emitter");
        node->SetScale(5.0f);
        emitter = (ParticleEmitter*)node->CloneComponent(emitters[0]);
        emitter->SetEffect(emitters[0]->GetEffect());
        emitters.Push(emitter);
    }

    emitter->GetNode()->SetPosition(position);
    emitter->SetEmitting(true);
    */
}

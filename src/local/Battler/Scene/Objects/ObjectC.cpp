// 2021/02/26 16:25:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Battler.h"
#include "Scene/SceneC.h"
#include "Scene/Objects/Object_.h"
#include "Scene/Objects/ObjectC.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"


HashMap<uint, ObjectT *> ObjectSpecificC::remoteStorage;


ObjectSpecific *ObjectSpecific::Create(ObjectT *object)
{
    return new ObjectSpecificC(object);
}


ObjectSpecificC::ObjectSpecificC(ObjectT *object) : ObjectSpecific(object)
{

}


ObjectT *ObjectSpecificC::GetFromID(uint id)
{
    ObjectT *object = remoteStorage[id];

    if (object)
    {
        return object;
    }

    if (ObjectT::empty == nullptr)
    {
        ObjectT::empty = (ObjectT *)(-1);               // Чтобы избежать рекурсивного вызова
        ObjectT::empty = TheScene->CreateChild("", LOCAL)->CreateComponent<Tank>();
        ObjectT::empty->SetEnabled(false);
    }

    return ObjectT::empty;
}


void ObjectSpecificC::OnPostRenderUpdate()
{
    if (TheBattler->drawDebug)
    {
        PhysicsParameters &physics = *object->physics;

        Vector3 pos = physics.pos.GetWorld() + Vector3::UP / 20.0f;

        float d = 1.0f;

        Vector3 dir = physics.dir.GetWorldDir() * d;
        Vector3 up = physics.dir.GetWorldUp() * d;
        Vector3 right = physics.dir.GetWorldRight() * d;

        TheDebugRenderer->AddLine(pos, pos + dir, Color::RED);
        TheDebugRenderer->AddLine(pos, pos + up, Color::GREEN);
        TheDebugRenderer->AddLine(pos, pos + right, Color::BLUE);
    }
}


template<class T> T *ObjectCreator::Create()
{
    return TheScene->CreateChild("", LOCAL)->CreateComponent<T>(LOCAL);
}

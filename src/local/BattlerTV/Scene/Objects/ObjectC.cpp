// 2021/02/26 16:25:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Battler.h"
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
        Node *node = object->GetObjectNode();

        Vector3 pos = node->GetWorldPosition();

        Vector3 dir = node->GetWorldDirection();
        Vector3 dir2 = dir + dir;

        TheDebugRenderer->AddLine(pos + Vector3::UP / 20.0f, dir + pos + Vector3::UP / 20.0f, Color::RED);
        
        
//        TheDebugRenderer->AddLine(dir + pos + Vector3(0.0f, 0.1f, 0.0f), dir + pos + Vector3(1.0f, 0.0f, 0.0f), Color::RED);
//        TheDebugRenderer->AddLine(dir + pos + Vector3(0.0f, 0.1f, 0.0f), dir + pos + Vector3(0.0f, 1.0f, 0.0f), Color::GREEN);
//        TheDebugRenderer->AddLine(dir + pos + Vector3(0.0f, 0.1f, 0.0f), dir + pos + Vector3(0.0f, 0.0f, 1.0f), Color::BLUE);
    }
}

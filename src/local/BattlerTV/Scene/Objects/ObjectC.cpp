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

        float d = 1.0f;

        Vector3 dir = node->GetWorldDirection() * d;
        Vector3 up = node->GetWorldUp() * d;
        Vector3 right = node->GetWorldRight() * d;

        Vector3 delta = Vector3::UP / 20.0f;

//        TheDebugRenderer->AddLine(pos + delta, pos + dir + delta, Color::RED);
//        TheDebugRenderer->AddLine(pos + delta, pos + up + delta, Color::GREEN);
//        TheDebugRenderer->AddLine(pos + delta, pos + right + delta, Color::BLUE);
    }
}

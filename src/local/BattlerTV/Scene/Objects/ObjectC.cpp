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

        Vector3 start = node->GetWorldPosition();
        Vector3 delta(0.0f, 1.0f, 0.0f);
        delta *= node->GetWorldScale();
        Vector3 end = start + delta;

        TheDebugRenderer->AddLine(start, end, Color::GREEN);
    }
}

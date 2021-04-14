// 2021/03/03 21:07:15 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Game/Messages/GameMessages_.h"
#include "Scene/SceneS.h"
#include "Scene/Objects/Object_.h"
#include "Scene/Objects/ObjectS.h"
#include "Scene/Objects/Units/Air/AirPlane/AirPlane_.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"


template Tank     *ObjectCreator::Create<Tank>();
template AirPlane *ObjectCreator::Create<AirPlane>();


ObjectSpecific *ObjectSpecific::Create(ObjectT *object)
{
    return new ObjectSpecificS(object);
}


ObjectSpecificS::ObjectSpecificS(ObjectT *object) : ObjectSpecific(object)
{

}


template<class T> T *ObjectCreator::Create()
{
    return TheScene->CreateChild("", LOCAL)->CreateComponent<T>(LOCAL);
}


void ObjectSpecificS::Update(float dT)
{
    ObjectSpecific::Update(dT);

//    if (TheTime->GetElapsedTime() >= timeNextTimeSend)
//    {
//        Vector3 position = node->GetPosition();
//
//        TheServer->SendToAll(false, Message::SendTankPosition(node->GetName(), node->GetPosition()));
//
//        timeNextTimeSend = TheTime->GetElapsedTime() + 0.1f;
//    }
}

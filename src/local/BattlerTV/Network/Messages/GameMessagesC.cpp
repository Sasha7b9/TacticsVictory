// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Game/Messages/GameMessages_.h"
#include "Scene/Level_.h"
#include "Scene/SceneC.h"


namespace Message
{
    void Message::Handle(VariantMap &map)
    {
        MemoryBuffer msg(map[NetworkMessage::P_DATA].GetBuffer());

        if (id == CLNT_RETURN_LEVEL)
        {
            ((ReturnLevel *)this)->Handle(msg);
        }
        else if (id == CLNT_CREATE_COMPONENT)
        {
            ((CreateComponent *)this)->Handle(msg);
        }
        else if (id == CLNT_SEND_TANK_POSITION)
        {
            ((SendTankPosition *)this)->Handle(msg);
        }
    }
}


void Message::Message::Send(bool reliable)
{
    Connection *connection = TheNetwork->GetServerConnection();

    if (connection)
    {
        connection->SendMessage(id, reliable, reliable, buffer);
    }
}


void Message::ReturnLevel::Handle(MemoryBuffer &msg)
{
    LOG_FUNC_ENTER();

    TheLevel = new Level();

    TheLevel->Load(msg);

    TheScene->Create();

    ThePathIndicator = new PathIndicator();

    TheCamera = CameraT::Create();
}


void Message::CreateComponent::Handle(MemoryBuffer &msg)
{
    StringHash hash = msg.ReadStringHash();
    uint ID = msg.ReadUInt();
    Vector3 position = msg.ReadVector3();

    Component *component = TheScene->CreateComponent(hash, LOCAL, ID);
    component->GetNode()->SetPosition(position);

    if (hash == "Tank")
    {
        TheTerrain->PutIn((Tank *)component, (uint)position.z_, (uint)position.x_);
    }
}


void Message::SendTankPosition::Handle(MemoryBuffer &msg)
{
    uint ID = msg.ReadUInt();

    Component *component = TheScene->GetComponent(ID);

    if (component)
    {
        component->GetNode()->SetPosition(msg.ReadVector3());
    }
}

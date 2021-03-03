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
    static int counter = 0;

    counter++;

    if (counter % 1000 == 0)
    {
        LOGINFOF("Recived %d components", counter);
    }

    StringHash type = msg.ReadStringHash();
    String name = msg.ReadString();
    Vector3 position = msg.ReadVector3();

    Component *component = TheScene->CreateComponent(type, LOCAL);

    component->GetNode()->SetName(name);
    component->GetNode()->SetPosition(position);

    if (type == "Tank")
    {
        TheTerrain->PutIn((Tank *)component, (uint)position.z_, (uint)position.x_);
    }
}


void Message::SendTankPosition::Handle(MemoryBuffer &msg)
{
    static String temp("");

    String name = msg.ReadString();

    if (temp == "")
    {
        temp = name;
    }

    Node *node = TheScene->GetChild(name);

    if (node)
    {
        Vector3 position = msg.ReadVector3();

        node->SetPosition(position);

        if (name == temp)
        {
            name = name;
        }

    }
}

// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Game/Messages/GameMessages_.h"
#include "Scene/Level_.h"
#include "Scene/SceneC.h"
#include "Scene/Cameras/Camera.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"


namespace Message
{
    void Message::Handle(VariantMap &map)
    {
        MemoryBuffer msg(map[NetworkMessage::P_DATA].GetBuffer());

        switch (id)
        {
        case CLNT_RETURN_LEVEL:       ((ReturnLevel *)this)->Handle(msg);      break;
        case CLNT_CREATE_COMPONENT:   ((CreateComponent *)this)->Handle(msg);  break;
        case CLNT_SEND_TANK_POSITION: ((SendTankPosition *)this)->Handle(msg); break;
        case CLNT_SEND_SCENE:         ((SendScene *)this)->Handle(msg);        break;
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
    String name = msg.ReadString();

    Node *node = TheScene->GetChild(name);

    if (node)
    {
        node->SetPosition(msg.ReadVector3());
    }
}


void Message::SendScene::Handle(MemoryBuffer &msg)
{
    TheScene->Decompress(msg);
}

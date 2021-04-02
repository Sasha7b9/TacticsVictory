// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Game/Connection_.h"
#include "Network/Game/Messages/GameMessages_.h"
#include "Scene/SceneS.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Scene/Terrain/Terrain_.h"


namespace Message
{
    void Message::Handle(VariantMap &map)
    {
        ConnectionT connection((Connection *)map[NetworkMessage::P_CONNECTION].GetPtr());

        MemoryBuffer msg(map[NetworkMessage::P_DATA].GetBuffer());

        switch (id)
        {
        case SERV_TEXTSTRING:        ((TextString *)this)->Handle(msg);             break;
        case SERV_REQUEST_FOR_LEVEL: ((RequestForLevel *)this)->Handle(connection); break;
        case SERV_KEY_EVENT:         ((KeyEvent *)this)->Handle(msg);               break;
        }
    }
}


void Message::RequestForLevel::Handle(const ConnectionT &connection)
{
    Vector3 position(10.0f, 10.0f, 10.0f);

    connection.SendMessage(true, ReturnLevel());

    for (ObjectT *object : ObjectT::storage)
    {
        connection.SendMessage(true,
            CreateGameObject(
                object->GetObjectNode()->GetID(),
                StringHash(object->GetTypeName()),
                object->physics->pos.GetWorld(),
                object->physics->rot.GetWorld()));
    }
}


Message::ReturnLevel::ReturnLevel() : Message(CLNT_RETURN_LEVEL)
{
    uint heightX = TheTerrain->HeightX();
    uint widthZ = TheTerrain->WidthZ();

    buffer.WriteUInt(heightX);
    buffer.WriteUInt(widthZ);

    for (uint row = 0; row < heightX; row++)
    {
        for (uint col = 0; col < widthZ; col++)
        {
            buffer.WriteFloat(TheTerrain->GetHeight(row, col));
        }
    }
}


Message::SendScene::SendScene() : Message(CLNT_SEND_SCENE)
{
    TheScene->Comporess(buffer);
}

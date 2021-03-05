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
                object->physics->pos.Get(),
                object->physics->rot.Get()));
    }
}


Message::ReturnLevel::ReturnLevel() : Message(CLNT_RETURN_LEVEL)
{
    uint height = TheTerrain->HeightX();
    uint width = TheTerrain->WidthZ();

    buffer.WriteUInt(height);
    buffer.WriteUInt(width);

    for (uint row = 0; row < height; row++)
    {
        for (uint col = 0; col < width; col++)
        {
            buffer.WriteFloat(TheTerrain->GetHeight(col, row));
        }
    }
}


Message::SendScene::SendScene() : Message(CLNT_SEND_SCENE)
{
    TheScene->Comporess(buffer);
}

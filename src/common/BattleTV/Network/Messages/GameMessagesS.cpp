// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Game/Connection_.h"
#include "Network/Game/Messages/GameMessages_.h"
#include "Scene/Objects/Units/Tank/Tank_.h"
#include "Scene/Terrain/Terrain_.h"


namespace Message
{
    void Message::Handle(VariantMap &map)
    {
        TConnection connection((Connection *)map[NetworkMessage::P_CONNECTION].GetPtr());

        MemoryBuffer msg(map[NetworkMessage::P_DATA].GetBuffer());

        if (id == SERV_TEXTSTRING)
        {
            ((TextString *)this)->Handle(msg);

        }
        else if (id == SERV_REQUEST_FOR_LEVEL)
        {
            ((RequestForLevel *)this)->Handle(connection);
        }
        else if (id == SERV_KEY_EVENT)
        {
            ((KeyEvent *)this)->Handle(msg);
        }
    }
}


void Message::RequestForLevel::Handle(const TConnection &connection)
{
    LOG_FUNC_ENTER();

    Vector3 position(10.0f, 10.0f, 10.0f);

    connection.SendMessage(true, ReturnLevel());

    static int counter = 0;

    for (Tank *tank : Tank::storage)
    {
        LOGINFOF("Send tank %d", counter++);

        connection.SendMessage(true, CreateComponent(tank->GetID(), tank->GetNode()->GetPosition()));
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

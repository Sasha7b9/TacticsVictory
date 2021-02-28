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
        else if (id == CLNT_CREATE_UNIT_TANK)
        {
            ((CreateUnitTank *)this)->Handle(msg);
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


void Message::CreateUnitTank::Handle(MemoryBuffer &msg)
{
    Vector3 position = msg.ReadVector3();

    TheTerrain->PutIn(TheScene->CreateComponent<Tank>(LOCAL), (uint)position.z_, (uint)position.x_);
}

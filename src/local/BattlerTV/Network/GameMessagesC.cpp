// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Game/GameMessages_.h"
#include "Scene/Scene_.h"


void Message::Message::Send(bool reliable)
{
    Connection *connection = TheNetwork->GetServerConnection();

    if (connection)
    {
        connection->SendMessage(id, reliable, reliable, buffer);
    }
}


void Message::BuildScene::Handle(MemoryBuffer & /*msg*/)
{
    TheScene->Create();
}

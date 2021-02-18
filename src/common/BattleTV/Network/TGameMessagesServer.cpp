/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"
#include "Network/Game/_TConnection.h"
#include "Network/Game/_TGameMessages.h"


void Message::RequestForBuildScene::Handle(const TConnection &connection)
{
    Vector3 position(10.0f, 10.0f, 10.0f);

    connection.SendMessage(true, BuildScene(position));
}


void Message::KeyEvent::Handle(MemoryBuffer &msg)
{
    UNUSED(msg);
}

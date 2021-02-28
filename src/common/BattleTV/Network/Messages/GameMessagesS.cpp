// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Game/Connection_.h"
#include "Network/Game/Messages/GameMessages_.h"


void Message::RequestForLevel::Handle(const TConnection &connection)
{
    Vector3 position(10.0f, 10.0f, 10.0f);

    connection.SendMessage(true, ReturnLevel(position));
}

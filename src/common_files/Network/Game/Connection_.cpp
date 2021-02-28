// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Game/Connection_.h"
#include "Network/Game/Messages/GameMessages_.h"


void TConnection::SendMessage(bool reliable, const Message::Message &message) const
{
    if (self)
    {
        self->SendMessage(message.id, reliable, reliable, message.buffer);
    }
}

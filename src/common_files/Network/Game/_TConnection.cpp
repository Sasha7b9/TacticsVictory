// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Game/_TConnection.h"
#include "Network/Game/_TGameMessages.h"


void TConnection::SendMessage(bool reliable, const Message::Message &message) const
{
    if (self)
    {
        self->SendMessage(message.id, reliable, reliable, message.buffer);
    }
}

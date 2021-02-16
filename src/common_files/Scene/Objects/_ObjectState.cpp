/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"


void ObjectState::Send() const
{
#ifdef SERVER

    if (connections.Size())
    {
        TConnection(connections[connections.Size() - 1]).SendMessage(true, Message::SendObjectState(*this));
    }

#endif
}

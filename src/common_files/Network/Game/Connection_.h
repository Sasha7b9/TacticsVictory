// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Message
{
    struct Message;
}


class ConnectionT
{
public:
    ConnectionT(Connection *connection) : self(connection) {}

    void SendMessage(bool reliable, const Message::Message &message) const;

    Connection *self = nullptr;
};

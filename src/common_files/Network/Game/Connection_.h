// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Message
{
    struct Message;
}


class ConnectionT : public Object
{
    URHO3D_OBJECT(ConnectionT, Object);
public:
    ConnectionT(Connection *connection = nullptr) : Object(TheContext), self(connection) {}

    ConnectionT(const ConnectionT &connection) : Object(TheContext)
    {
        self = connection.self;
    }

    void SendMessage(bool reliable, const Message::Message &message) const;

    Connection *self = nullptr;

    bool operator!=(const ConnectionT &rhs) { return rhs.self != self; }
    ConnectionT &operator=(const ConnectionT &rhs) { self = rhs.self; return *this; }
};

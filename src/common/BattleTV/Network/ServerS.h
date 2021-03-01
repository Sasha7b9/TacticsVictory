// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Network/Game/Messages/GameMessages_.h"


class TConnection;


class ServerS : public Object
{
    URHO3D_OBJECT(ServerS, Object);

public:

    ServerS(Context *context = TheContext);

    bool Start(uint16 port);

    void SendToAll(const Message::Message &message);

private:

    Vector<TConnection> connections;

    void HandleMessage(StringHash, VariantMap &);

    void HandleServerConnected(StringHash, VariantMap &);

    void HandleServerDisconnected(StringHash, VariantMap &);

    void HandleClientConnected(StringHash, VariantMap &);

    void HandleCliendDisconnected(StringHash, VariantMap &);

    void HandleConnectFailed(StringHash, VariantMap &);
};
// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Network/Game/Connection_.h"
#include "Network/Game/Messages/GameMessages_.h"


class ServerS : public Object
{
    URHO3D_OBJECT(ServerS, Object);

public:

    ServerS(ServerS **self);

    bool Start(uint16 port);

    void SendToAll(bool reliable, const Message::Message &message);

private:

    Vector<ConnectionT> connections;

    void HandlerMessage(StringHash, VariantMap &);
    void HandlerServerConnected(StringHash, VariantMap &);
    void HandlerServerDisconnected(StringHash, VariantMap &);
    void HandlerClientConnected(StringHash, VariantMap &);
    void HandlerCliendDisconnected(StringHash, VariantMap &);
    void HandlerConnectFailed(StringHash, VariantMap &);
};

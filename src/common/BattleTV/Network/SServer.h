// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"


class SServer : public Object
{
    URHO3D_OBJECT(SServer, Object);

public:

    SServer(Context *context);

    bool Start(uint16 port);

private:

    void HandleMessage(StringHash, VariantMap &);

    void HandleServerConnected(StringHash, VariantMap &);

    void HandleServerDisconnected(StringHash, VariantMap &);

    void HandleClientConnected(StringHash, VariantMap &);

    void HandleCliendDisconnected(StringHash, VariantMap &);

    void HandleConnectFailed(StringHash, VariantMap &);
};
// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


/*
*  Класс для коммуникаций с сервером
*/

class CServer : public Object
{
    URHO3D_OBJECT(CServer, Object);

public:

    CServer(Context *context);

    void Connect(const String &address, uint16 port);

private:

    void HandleMessage(StringHash, VariantMap &);

    void HandleServerConnected(StringHash, VariantMap &);

    void HandleServerDisconnected(StringHash, VariantMap &);

    void HandleConnectFailed(StringHash, VariantMap &);
};

#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class VectorBufferRTS;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Client : public Object
{
    URHO3D_OBJECT(Client, Object);

public:
    Client(Context *context = gContext);
    virtual ~Client();
    void StartConnecting(const String &address, uint16 port, pFuncVV funcOnConnect);
    bool IsConnected();
    Connection *GetServerConnection();
    void Send(int msgID, const VectorBufferRTS &msg);
    void Disconnect();
    uint16 GetPort();

private:
    Network *network = nullptr; //-V122
    pFuncVV funcOnConnect = nullptr; //-V122
    Connection *connection = nullptr; //-V122

    void HandleServerConnected(StringHash, VariantMap&);
    void HandleServerDisconnected(StringHash, VariantMap&);

    DEFAULT_MEMBERS(Client);
};


#define IN_CLIENT_MODE (gClient->IsConnected())

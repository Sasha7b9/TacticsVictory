#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class VectorBufferRTS;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Server : public Object
{
    URHO3D_OBJECT(Server, Object);

public:
    Server(Context *context = gContext);
    virtual ~Server();
    bool Start(uint16 port);
    bool IsRunning();
    Vector<SharedPtr<Connection>> GetConnections();
    void SendToAll(int msgID, const VectorBufferRTS &msg);
    void Disconnect();
    void SetSimulatedLatency(int timeMS);
    void SetSimulatedPacketLoss(float probability);

private:
    Network *network = nullptr; //-V122

    DEFAULT_MEMBERS(Server);
};


#define IN_SERVER_MODE (gServer->IsRunning())

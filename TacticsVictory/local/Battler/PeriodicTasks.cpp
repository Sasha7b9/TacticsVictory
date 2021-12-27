// 2021/12/24 22:00:15 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "PeriodicTasks.h"
#include "Network/Messages/MessagesClient_.h"
#include "Objects/GameObject_.h"


using namespace Pi;


void TaskConnecting::Step()
{
    TheMessageMgr->DisconnectAll();

    TheNetworkMgr->SetProtocol(kGameProtocol);
    TheNetworkMgr->SetPortNumber(0);
    TheNetworkMgr->SetBroadcastPortNumber(PORT_NUMBER);
    PiResultNetwork::B result = TheMessageMgr->BeginMultiplayerGame(false);

    if (result != PiResultNetwork::Okay)
    {
        LOG_ERROR_TRACE("Can not begin mulitplayer game");
    }

    NetworkAddress address = MessageMgr::StringToAddress(REMOTE_ADDRESS);
    address.SetPort(PORT_NUMBER);

    if (TheMessageMgr->Connect(address) != PiResultNetwork::Okay)
    {
        LOG_ERROR_TRACE("Can not connect to %s:%d", REMOTE_ADDRESS, PORT_NUMBER);
    }
    else
    {
        LOG_WRITE("Attempt connection to %s:%d ...", REMOTE_ADDRESS, PORT_NUMBER);
    }

    complete = true;
}


void TaskPing::Step()
{
    TheMessageMgr->SendMessage(PlayerType::Server, MessagePing());
}


void TaskTraffic::Step()
{
    static uint prev_recv = 0;
    static uint prev_send = 0;
    
    uint recv = TheNetworkMgr->GetBytesRecv();
    uint send = TheNetworkMgr->GetBytesSend();
    
    int num_units = GameObject::objects.GetElementCount();
    
    LOG_WRITE("traffic in/out %.1f/%.1f kB/s %d bytes/unit %d", (float)(recv - prev_recv) / 1024.0f,
                                                                (float)(send - prev_send) / 1024.0f,
                                                                (recv - prev_recv) / num_units, num_units);
    prev_recv = recv;
    prev_send = send;
}


void TaskProfiler::Step()
{
    PROFILER_LOG_FULL();
}


void TaskProfilerLastFrame::Step()
{
    PROFILER_LOG_LAST_FRAME();
}

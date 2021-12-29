// 2021/12/24 22:00:15 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "PeriodicTasks.h"
#include "Network/Messages/MessagesClient_.h"
#include "Objects/GameObject_.h"
#include "Utils/Math_.h"


using namespace Pi;


void TaskConnecting::RunOnce()
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


void TaskPing::RunOnce()
{
    TheMessageMgr->SendMessage(PlayerType::Server, MessagePing());
}


void TaskProfiler::RunOnce()
{
    PROFILER_LOG_FULL();
}


void TaskProfilerLastFrame::RunOnce()
{
    PROFILER_LOG_LAST_FRAME();
}


int TaskMain::NumberThreads()
{
    return M::LimitationAbove(TheEngine->GetProcessorCount(), 32);
}

// 2021/12/25 19:33:37 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Utils/PeriodicTask_.h"
#include "Objects/GameObject_.h"


using namespace Pi;


void PeriodicTask::Setup(uint periodMS, int _times)
{
    nextTime = TheTimeMgr->GetMillisecondCount();
    period = periodMS;
    times = _times;
    complete = false;
}


void PeriodicTask::Update()
{
    uint time = TheTimeMgr->GetMillisecondCount();

    if (time >= nextTime)
    {
        RunOnce();

        nextTime += period;

        if (times > 0)
        {
            times--;
            if (times == 0)
            {
                complete = true;
            }
        }
    }
}


void ListPeriodicTask::Append(PeriodicTask *task, uint period, int times)
{
    task->Setup(period, times);
    tasks.Append(task);
}


void ListPeriodicTask::Remove(PeriodicTask *task)
{
    tasks.Remove(task);
}


bool ListPeriodicTask::Consist(PeriodicTask *task)
{
    return tasks.Member(task);
}


void ListPeriodicTask::Run()
{
    PeriodicTask *task = tasks.First();

    while (task)
    {
        task->Update();
        if (task->Complete())
        {
            tasks.Remove(task);
        }
        task = task->Next();
    }
}


void ListPeriodicTask::Purge()
{
    tasks.RemoveAll();
}


void TaskTraffic::RunOnce()
{
    static uint prev_recv = 0;
    static uint prev_send = 0;

    uint recv = TheNetworkMgr->GetBytesRecv();
    uint send = TheNetworkMgr->GetBytesSend();

    int num_units = GameObject::objects.GetElementCount();

    if (num_units == 0)
    {
        LOG_WRITE("traffic in/out %.1f/%.1f kB/s, %d units", (float)(recv - prev_recv) / 1024.0f,
            (float)(send - prev_send) / 1024.0f,
            num_units);
    }
    else
    {
        LOG_WRITE("traffic in/out %.1f/%.1f kB/s, %d/%d bytes/unit, %d units", (float)(recv - prev_recv) / 1024.0f,
            (float)(send - prev_send) / 1024.0f,
            (recv - prev_recv) / num_units,
            (send - prev_send) / num_units,
            num_units);
    }

    prev_recv = recv;
    prev_send = send;
}

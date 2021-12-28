// 2021/12/25 19:33:37 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Utils/PeriodicTask_.h"


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

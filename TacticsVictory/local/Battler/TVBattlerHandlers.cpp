// 2021/12/4 22:36:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "TVBattler.h"
#include "Scene/World/GameWorld.h"
#include "Scene/World/Landscape_.h"
#include "Network/Messages/MessagesClient_.h"
#include "GameState.h"
#include "Objects/GameObject_.h"


using namespace Pi;


void Battler::HandleOnButtonQuit(Widget *, const WidgetEventData *)
{
    TheEngine->Quit();
}


void Battler::HandleGizmoCommand(Command *, pchar)
{
}


void Battler::HandleFogDensityCommand(Command *, pchar text)
{
    float density = Text::StringToFloat(text);

    Water::SetFogDensity(density);
}


void Battler::HandlePingCommand(Command *, pchar)
{
    TaskPing &task = *TaskPing::Self();

    task.ToggleLogging();

    if (task.EnabledLogging())
    {
        LOG_WRITE("ping on");
    }
    else
    {
        LOG_WRITE("ping off");
    }
}


void Battler::HandleTrafficCommand(Command *, pchar)
{
    ListPeriodicTask &tasks = *ListPeriodicTask::Self();
    TaskTraffic *task = TaskTraffic::Self();

    if (tasks.Consist(task))
    {
        tasks.Remove(task);
        LOG_WRITE("traffic off");
    }
    else
    {
        tasks.Append(task, 1000);
        LOG_WRITE("traffic on");
    }
}


void Battler::HandleServerCommand(Command *, pchar text)
{
    LOG_WRITE("Need send on server \"%s\"", text);
}

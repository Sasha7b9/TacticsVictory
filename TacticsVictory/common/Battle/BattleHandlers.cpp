// 2021/12/4 22:36:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Battle.h"
#include "Scene/World/GameWorld.h"
#include "Scene/Objects/Units/PathFinder/PathUnit.h"
#include "Scene/World/Landscape.h"


using namespace Pi;


void Battle::HandleDisplayEvent(const DisplayEventData *eventData, void * /*cookie*/)
{
    if (eventData->eventType == EventDisplay::Change)
    {
    }
}


void Battle::HandleGameEvent(GameEvent::E event, const void *param)
{
    if (event == GameEvent::E::GameSynchronized)
    {
    }
}


void Battle::ApplicationTask()
{
}


void Battle::HandleOnButtonQuit(Widget *, const WidgetEventData *)
{
    TheEngine->Quit();
}

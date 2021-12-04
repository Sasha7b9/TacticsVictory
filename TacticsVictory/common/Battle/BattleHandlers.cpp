// 2021/12/4 22:36:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Battle.h"
#include "Scene/World/GameWorld.h"
#include "Scene/Objects/Units/PathFinder/WaveAlgorithm.h"
#include "Scene/World/Landscape.h"


using namespace Pi;


void Battle::HandleDisplayEvent(const DisplayEventData *eventData, void * /*cookie*/)
{
    if (eventData->eventType == EventDisplay::Change)
    {
    }
}


void Battle::ApplicationTask()
{
    static bool first = true;
    static bool completed = false;

    static uint timeStart = TheTimeMgr->GetMillisecondCount();

    if (first)
    {
        if(GameWorld::Get()->GetLandscape()->IsCreated())
        {
            first = false;
            WaveAlgorithm::Calculate({0.0f, 0.0f}, { (float)GameWorld::Get()->GetLandscape()->GetSizeX() - 1.0f, (float)GameWorld::Get()->GetLandscape()->GetSizeY() - 1.0f });
        }
    }
    else if (!completed)
    {
        if (WaveAlgorithm::PathIsFound())
        {
            Array<Point2D> path = WaveAlgorithm::GetPath();

            TheConsoleWindow->AddText(Text::Format("Path found for %f seconds: %d elements", (float)(TheTimeMgr->GetMillisecondCount() - timeStart) / 1e3f, path.GetElementCount()));

            for (auto &point : path)
            {
                TheConsoleWindow->AddText(Text::Format("%f : %f", point.x, point.y));
            }

            TheConsoleWindow->AddText(" ");

            completed = true;
        }
        else
        {
            TheConsoleWindow->AddText("Calculated");
        }
    }
}


void Battle::HandleOnButtonQuit(Widget *, const WidgetEventData *)
{
    TheEngine->Quit();
}

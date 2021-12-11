// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "Battle.h"
#include "GUI/GUI.h"
#include "GUI/Widgets/CursorGUI.h"
#include "Input/Mouse.h"
#include "Scene/Objects/GameObject.h"
#include "Scene/World/GameWorld.h"
#include "Scene/World/Landscape.h"
#include "Scene/World/Sun.h"
#include "Scene/World/WorldGizmo.h"
#include "Scene/Objects/Units/Ground/Tank.h"


using namespace Pi;


Sun *sun = nullptr;
Sun *sunViewport = nullptr;


namespace Pi
{
    GameWorld *GameWorld::self = nullptr;
}


GameWorld::GameWorld(pchar name)
    : World(name)
{
    self = this;
}

GameWorld::~GameWorld()
{
    SAFE_DELETE(CursorGUI::self);
    SAFE_DELETE(sun);
}

const LocatorMarker *GameWorld::FindSpectatorLocator(const Zone *zone)
{
    const Marker *marker = zone->GetFirstMarker();
    while(marker)
    {
        if(marker->Enabled())
        {
            PiTypeMarker::S type = marker->GetMarkerType();

            if(type == PiTypeMarker::Locator)
            {
                const LocatorMarker *locator = static_cast<const LocatorMarker *>(marker);
                if(locator->GetLocatorType() == PiTypeLocator::Spectator)
                {
                    return (locator);
                }
            }
        }

        marker = marker->Next();
    }

    const Zone *subzone = zone->GetFirstSubzone();
    while(subzone)
    {
        const LocatorMarker *locator = FindSpectatorLocator(subzone);
        if(locator)
        {
            return (locator);
        }

        subzone = subzone->Next();
    }

    return (nullptr);
}


WorldResult::B GameWorld::Preprocess()
{
    WorldResult::B result = World::Preprocess();

    if(result != WorldResult::Okay)
    {
        return (result);
    }

    SetCamera(CameraRTS::self);
    CameraRTS::self->Invalidate();
    CameraRTS::self->Update();

    landscape = new Landscape((Battle::self->DataPath() + "levels/level2.lvl").c_str(), 0.1f);
    GetRootNode()->AppendNewSubnode(landscape);

    sun = new Sun();

    static_cast<SunController*>(sun->GetController())->SetParameters({ 10.0f, -5.0f, 5.0f });
    GetRootNode()->AppendNewSubnode(sun);

    sunViewport = new Sun();
    GetRootNode()->AppendNewSubnode(sunViewport);

    GetRootNode()->AppendNewSubnode(new WorldGizmo());

    return (WorldResult::Okay);
}


void GameWorld::Render()
{
    World::Render();
}


void GameWorld::Move()
{
    World::Move();

    static bool created = false;

    if (!created && landscape->IsCreated())
    {
        created = true;

        for (int i = 0; i < 100; i++)
        {
            GameObject *tank = Tank::Create();
            tank->SetMapPosition((float)Math::Random(0, landscape->GetSizeX_Columns() - 1), (float)Math::Random(0, landscape->GetSizeY_Rows() - 1));
            GameWorld::Get()->AppendGameObject(tank);
        }
    }
}


void GameWorld::ChangeCursorPosition(float deltaX, float deltaY)
{
    CursorGUI::self->position.x += deltaX * 3.0F;
    CursorGUI::self->position.y += deltaY * 3.0F;

    float displayWidth = (float)TheDisplayMgr->GetDisplayWidth();
    float displayHeight = (float)TheDisplayMgr->GetDisplayHeight();

    CursorGUI::self->position.x = FmaxZero(CursorGUI::self->position.x);
    CursorGUI::self->position.y = FmaxZero(CursorGUI::self->position.y);

    CursorGUI::self->position.x = Fmin(displayWidth - 1,  CursorGUI::self->position.x);
    CursorGUI::self->position.y = Fmin(displayHeight - 1, CursorGUI::self->position.y);

    Vector2D cursorSize = CursorGUI::self->GetWidgetSize();
    float posX = CursorGUI::self->position.x - 0.5F * cursorSize.x;
    float posY = CursorGUI::self->position.y - 0.5F * cursorSize.y;

    CursorGUI::self->SetWidgetPosition(Point3D((float)((int)posX), (float)((int)posY), 0.0F));
    CursorGUI::self->Invalidate();

    if(GUI::self)
    {
        Mouse::self->ChangePos((int)posX, (int)posY);
    }
}


GameWorld *GameWorld::Get()
{
    static GameWorld empty("world/Empty");

    GameWorld *world = (GameWorld *)TheWorldMgr->GetWorld();

    return world ? world : &empty;
}


Point3D GameWorld::TransformWorldCoordToDisplay(const Point3D &worldPosition)
{
    // Transform the world point into camera space
    Point3D displayPoint = CameraRTS::self->GetInverseWorldTransform() * worldPosition;

    // Project the point onto the focal plane
    const FrustumCameraObject *object = CameraRTS::self->GetObject();
    float focalLength = object->GetFocalLength();
    displayPoint.x *= focalLength / displayPoint.z;
    displayPoint.y *= focalLength / displayPoint.z;

    // Rescale to the width and height of the display
    float w = (float)(TheDisplayMgr->GetDisplayWidth() / 2);
    float h = (float)(TheDisplayMgr->GetDisplayHeight() / 2);
    displayPoint.x = w * displayPoint.x + w;
    displayPoint.y = h * displayPoint.y / object->GetAspectRatio() + h;
    displayPoint.z = 0.0f;

    return displayPoint;
}


void GameWorld::AppendGameObject(GameObject *object)
{
    Get()->GetRootNode()->AppendNewSubnode(object);
}

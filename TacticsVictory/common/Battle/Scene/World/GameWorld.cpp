// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Battle.h"
#include "GUI/GUI.h"
#include "GUI/Widgets/CursorGUI.h"
#include "Input/Mouse.h"
#include "Objects/GameObject.h"
#include "Scene/World/GameWorld.h"
#include "Scene/World/Landscape.h"
#include "Scene/World/Sun.h"
#include "Graphics/Meshes/WorldGizmo.h"
#include "Objects/Units/Ground/Tank.h"
#include "Graphics/Textures/PoolTextures.h"
#include "Objects/Units/Selector/Selector.h"
#include "Objects/Units/Air/Airplane.h"
#include "Scene/World/Water.h"
#include "Objects/Units/UnitLogic/UnitTask.h"
#include "Objects/Units/Water/Submarine.h"


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


static void AppendObject(GameObject *object)
{
    Landscape *landscape = GameWorld::self->GetLandscape();

    int sizeX = landscape->GetSizeX_Columns();
    int sizeY = landscape->GetSizeY_Rows();

    bool added = false;

    while (!added)
    {
        added = object->AppendInGame(std::rand() % sizeX, std::rand() % sizeY);
    }
}


static void CreateObjects(GameWorld *world)
{
    for (int i = 0; i < 50; i++)
    {
        AppendObject(Tank::Create());

        AppendObject(Airplane::Create());

        Submarine *submarine = Submarine::Create();

        AppendObject(submarine);

        submarine->GetController<UnitController>()->AppendTask(new DiveUnitTaskAbs(-5.0f));
    }

    world->GetRootNode()->AppendNewSubnode(new Selector());
}


void GameWorld::Move()
{
    World::Move();

    static bool created = false;

    if (!created && landscape->IsCreated())
    {
        created = true;

        self = this;

        Water::Create();

        CreateObjects(Get());
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

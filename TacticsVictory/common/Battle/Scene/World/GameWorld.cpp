#include <stdafx.h>
#include "Battle.h"
#include "GUI/GUI.h"
#include "GUI/Widgets/CursorGUI.h"
#include "Input/Mouse.h"
#include "Scene/Objects/GameObject.h"
#include "Scene/World/GameWorld.h"
#include "Scene/World/Landscape.h"
#include "Scene/World/Sun.h"
#include "Scene/World/WorldGismo.h"
#include "Scene/Objects/Units/Ground/Tank.h"
#include "Scene/Objects/Units/PathUnit.h"


using namespace Pi;


Sun *sun = nullptr;
Sun *sunViewport = nullptr;


GameWorld::GameWorld(pchar name)
    : World(name)
{
}

GameWorld::~GameWorld()
{
    SAFE_DELETE(TheCursor);

}

const LocatorMarker *GameWorld::FindSpectatorLocator(const Zone *zone)
{
    const Marker *marker = zone->GetFirstMarker();
    while(marker)
    {
        if(marker->Enabled())
        {
            MarkerType::S type = marker->GetMarkerType();

            if(type == MarkerType::Locator)
            {
                const LocatorMarker *locator = static_cast<const LocatorMarker *>(marker);
                if(locator->GetLocatorType() == kLocatorSpectator)
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

    SetCamera(TheCamera);
    TheCamera->Invalidate();
    TheCamera->Update();

    landscape = new Landscape((TheBattle->DataPath() + "levels/level2.lvl").c_str(), 0.1f);
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
            tank->SetMapPosition((float)Math::Random(0, landscape->GetSizeX() - 1), (float)Math::Random(0, landscape->GetSizeY() - 1));
            GameWorld::Get()->AppendGameObject(tank);
        }

        PathUnit::Create();
    }

    if(created)
    {
        bool result = false;
        Point3D point = landscape->GetPointScreen(TheCursor->position.x, TheCursor->position.y, result);
        PathUnit::SetPosition(point);
        result ? PathUnit::PowerOn() : PathUnit::PowerOff();
    }
}


void GameWorld::ChangeCursorPosition(float deltaX, float deltaY)
{
    TheCursor->position.x += deltaX * 3.0F;
    TheCursor->position.y += deltaY * 3.0F;

    float displayWidth = (float)TheDisplayMgr->GetDisplayWidth();
    float displayHeight = (float)TheDisplayMgr->GetDisplayHeight();

    TheCursor->position.x = FmaxZero(TheCursor->position.x);
    TheCursor->position.y = FmaxZero(TheCursor->position.y);

    TheCursor->position.x = Fmin(displayWidth - 1, TheCursor->position.x);
    TheCursor->position.y = Fmin(displayHeight - 1, TheCursor->position.y);

    Vector2D cursorSize = TheCursor->GetWidgetSize();
    float posX = TheCursor->position.x - 0.5F * cursorSize.x;
    float posY = TheCursor->position.y - 0.5F * cursorSize.y;

    TheCursor->SetWidgetPosition(Point3D((float)((int)posX), (float)((int)posY), 0.0F));
    TheCursor->Invalidate();

    if(TheGUI)
    {
        TheMouse->ChangePos((int)posX, (int)posY);
    }
}


GameObject *GameWorld::GameObjectInPosition(const Point2D &coord)
{
    GameObjectProperty *property = GameObjectPropertyInPosition(coord);

    return property ? property->GetGameObject() : nullptr;
}


GameObjectProperty *GameWorld::GameObjectPropertyInPosition(const Point2D &coord)
{
    Ray ray = TheCamera->GetWorldRayFromPoint(coord);

    CollisionData data;

    Point3D p1 = ray.origin;
    Point3D p2 = p1 + ray.direction * ray.tmax;

    if (DetectCollision(p1, p2, 0.0f, PiKindCollision::RigidBody, &data))
    {
        Node *node = data.geometry->GetSuperNode();

        while (node)
        {
            GameObjectProperty *property = (GameObjectProperty *)node->GetProperty(PiTypeProperty::GameObject);

            if (property)
            {
                return property;
            }

            node = node->GetSuperNode();
        }
    }

    return nullptr;
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
    Point3D displayPoint = TheCamera->GetInverseWorldTransform() * worldPosition;

    // Project the point onto the focal plane
    const FrustumCameraObject *object = TheCamera->GetObject();
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

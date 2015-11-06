#include <stdafx.h>


#include "Scene.h"
#include "Core/Camera.h"
#include "Core/Math.h"
#include "Game/Logic/Movinator.h"
#include "Game/Level.h"
#include "Game/Objects/Terrain.h"
#include "GUI/Elements/Cursor.h"
#include "Game/Path/TilePath.h"


Scene::Scene(Context *context) :
    Object(context)
{
    RegisterObjects();

    Create();

    pathIndicator.Init();

    SubscribeToEvent(Urho3D::E_MOUSEBUTTONDOWN, HANDLER(Scene, HandleMouseDown));
}

Scene::~Scene()
{
    pathIndicator.Stop();
}

void Scene::RegisterObjects()
{
    Tank::RegisterObject();
}

void Scene::RegisterObject(Context *context)
{
    context->RegisterFactory<Scene>();
}

void Scene::Create()
{
    // Create a Zone component into a child scene node. The Zone controls ambient lighting and fog settings. Like the Octree,
    // it also defines its volume with a bounding box, but can be rotated (so it does not need to be aligned to the world X, Y
    // and Z axes.) Drawable objects "pick up" the zone they belong to and use it when rendering; several zones can exist

    Node* zoneNode = gScene->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    // Set same volume as the Octree, set a close bluish fog and some ambient light
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    //zone->SetFogColor(Color::BLUE);
    //zone->SetFogHeightScale(10000.0f);
    //zone->SetFogStart(0.0f);
    //zone->SetFogEnd(1000.0f);
    float dColor = 0.1f;
    zone->SetAmbientColor(Color(dColor, dColor, dColor));

    Vector<Vector<float>> level = gLevel->Load("TVData/Game/Levels/level.map");
    gTerrain = new Terrain(level);

    for (int i = 0; i < 100; i++)
    {
        int col = Math::RandomInt(0, (int)gLevel->GetWidth() - 1);
        int row = Math::RandomInt(0, (int)gLevel->GetHeight() - 1);

        for (auto tank : tanks)
        {
            Vector3 pos = tank->GetPosition();
            if ((int)pos.x_ == col && -(int)pos.z_ == row)
            {
                i--;
                continue;
            }
        }

        SharedPtr<Node> nodeTank(gScene->CreateChild(NODE_TANK));
        SharedPtr<Tank> tank(nodeTank->CreateComponent<Tank>());
        tank->Init(Tank::Small);
        tank->SetCoord({(uint)row, (uint)col});
        tank->SetAutoReloaded(1);
    }

    SharedPtr<Node> lightNode;
    lightNode = gScene->CreateChild("LigthNode");
    Movinator *movinator = lightNode->CreateComponent<Movinator>();
    movinator->SetCenter({level[0].Size() / 2.0f, 25.0f, -(level.Size() / 2.0f)});
    movinator->SetMoveSpeed(0.5f);

    ULight *light = lightNode->CreateComponent<ULight>();
    lightNode->SetScale(0.01f);
    light->SetLightType(Urho3D::LIGHT_POINT);
    light->SetRange(1000.0f);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetEnabled(true);
    gRenderer->SetShadowMapSize(2048);

    uint sizeX = level[0].Size();
    uint sizeZ = level.Size();

    gCamera->SetPosition({sizeX / 2.0f, 25.0f, - (float)sizeZ / 2.0f - 10.0f}, {sizeX / 2.0f, 0.0f, -(sizeZ / 2.0f)});
}

void Scene::Update()
{
    Vector3 hitPos;
    Drawable *drawable = gCursor->GetRaycastNode(&hitPos);

    if (drawable)
    {
        String name = drawable->GetNode()->GetName();
        if(name == NODE_TERRAIN)
        {
            gCursor->SetNormal();
        }
        else if (name == NODE_TANK)
        {
            gCursor->SetSelected();
        }
    }
    else
    {
        gCursor->SetNormal();
    }

    pathIndicator.Update();
}

void Scene::HandleMouseDown(StringHash, VariantMap& eventData)
{
    int buttons = (int)eventData[Urho3D::MouseButtonDown::P_BUTTONS].GetInt();

    if(buttons != Urho3D::MOUSEB_LEFT)
    {
        if (buttons == Urho3D::MOUSEB_RIGHT)
        {
            pathIndicator.Enable(false);
        }
        return;
    }

    Vector3 hitCoord;
    Drawable *object = gCursor->GetRaycastNode(&hitCoord);

    if (!object)
    {
        return;
    }

    Node *node = object->GetNode();
    String name = node->GetName();

    if (name == NODE_TANK)
    {
        Tank *tank = node->GetComponent<Tank>();
        SetSelected(tank, !tank->IsSelected());

        Vector3 position = node->GetPosition();
        Coord coord((uint)-position.z_, (uint)(position.x_));

        pathIndicator.SetStartPosition(coord);
        pathIndicator.Enable(false);
        if(tank->IsSelected())
        {
            pathIndicator.Enable(true);
        }
    }
    else if (name == NODE_TERRAIN)
    {
        pathIndicator.Enable(false);
        Tank *tank = GetSelected();

        if(tank)
        {
            SetSelected(tank, false);
            tank->SetPath(pathIndicator.GetPath());
        }
    }
}

void Scene::SetSelected(Tank *tank, bool selected)
{
    if(selected)
    {
        const Vector<SharedPtr<Node>> &nodes = gScene->GetChildren();
        for(SharedPtr<Node> node : nodes)
        {
            Tank *tank = node->GetComponent<Tank>();
            if(tank)
            {
                tank->SetSelected(false);
            }
        }
    }
    tank->SetSelected(selected);
}

Tank* Scene::GetSelected()
{
    const Vector<SharedPtr<Node>> &nodes = gScene->GetChildren();

    for(SharedPtr<Node> node : nodes)
    {
        Tank *tank = node->GetComponent<Tank>();
        if(tank && tank->IsSelected())
        {
            return tank;
        }
    }
    
    return nullptr;
}

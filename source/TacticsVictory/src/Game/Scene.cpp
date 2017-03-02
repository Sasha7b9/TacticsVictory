#include <stdafx.h>
#include "Scene.h"
#include "Core/Camera.h"
#include "Core/Math.h"
#include "Game/Logic/Movinator.h"
#include "Game/Level.h"
#include "Game/Objects/Terrain/Terrain.h"
#include "Game/Objects/Terrain/Terrain.h"
#include "GUI/Cursor.h"
#include "Game/Path/TilePath.h"
#include "Game/Objects/Ammo/Rocket/Rocket.h"
#include "Game/Objects/Buildings/MilitaryPlant/MilitaryPlant.h"
#include "Game/Sounds.h"
#include "Game/Particles.h"
#include "GUI/GuiGame/WindowTarget.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SceneRTS::SceneRTS(Context *context) :
    Object(context)
{
    RegisterObjects();

    Create();

    pathIndicator.Init();

    SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(SceneRTS, HandleMouseDown));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
SceneRTS::~SceneRTS()
{
    SAFE_DELETE(gTerrain);
    pathIndicator.Stop();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void SceneRTS::RegisterObjects()
{
    Tank::RegisterObject();
    Rocket::RegisterObject();
    MilitaryPlant::RegisterObject();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void SceneRTS::RegisterObject(Context *context)
{
    context->RegisterFactory<SceneRTS>();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void SceneRTS::Create()
{
    Sounds::Init();

    Particles::Init();

    gPhysicsWorld->SetFps(5);

    // Create a Zone component into a child scene node. The Zone controls ambient lighting and fog settings. Like the Octree,
    // it also defines its volume with a bounding box, but can be rotated (so it does not need to be aligned to the world X, Y
    // and Z axes.) Drawable objects "pick up" the zone they belong to and use it when rendering; several zones can exist

    Node* zoneNode = gScene->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    // Set same volume as the Octree, set a close bluish fog and some ambient light
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetFogColor(Color::GRAY);
    zone->SetFogHeightScale(10000.0f);
    zone->SetFogStart(0.0f);
    zone->SetFogEnd(1000.0f);
    float dColor = 0.1f;
    zone->SetAmbientColor(Color(dColor, dColor, dColor));

    Vector<Vector<float>> level = gLevel->Load("Game/Levels/level.map");
    gTerrain = new TerrainRTS();
    gTerrain->CreateFromVector(level);

    /*
    for (int i = 0; i < 125; i++)
    {
        uint row = 0;
        uint col = 0;
        do
        {
            col = (uint)Math::RandomInt(0, (int)gLevel->GetWidth() - 1);
            row = (uint)Math::RandomInt(0, (int)gLevel->GetHeight() - 1);
        } while(gTerrain->GetHeight(row, col) != 0.0f);
        
        SharedPtr<Tank> tank = Tank::Create(Tank::Small);
        gTanks.Push(tank);
        tank->SetCoord({row, col});
        tank->SetAutoReloaded(1);
    }

    SharedPtr<Tank> tank = Tank::Create(Tank::Small);
    tank->SetCoord(Coord(0, 0));
    gTanks.Push(tank);

    tank = Tank::Create(Tank::Small);
    tank->SetCoord(Coord(0, 40));
    gTanks.Push(tank);

    tank = Tank::Create(Tank::Small);
    tank->SetCoord(Coord(40, 0));
    gTanks.Push(tank);

    tank = Tank::Create(Tank::Small);
    tank->SetCoord(Coord(40, 40));
    gTanks.Push(tank);
    */

    SharedPtr<Node> lightNode;
    lightNode = gScene->CreateChild("LigthNode");
    Movinator *movinator = lightNode->CreateComponent<Movinator>();
    movinator->SetCenter({level[0].Size() / 2.0f, 25.0f, -(level.Size() / 2.0f)});
    movinator->SetMoveSpeed(0.5f);

    Light *light = lightNode->CreateComponent<Light>();
    lightNode->SetScale(0.01f);
    light->SetLightType(LIGHT_POINT);
    light->SetRange(1000.0f);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00011f, 2.0f));
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetEnabled(true);
    gRenderer->SetShadowMapSize(2048);

    uint sizeX = level[0].Size();
    uint sizeZ = level.Size();

    gCamera->SetPosition({sizeX / 2.0f, 25.0f, - (float)sizeZ / 2.0f - 10.0f}, {sizeX / 2.0f, 0.0f, -(sizeZ / 2.0f)});

    gWindowTarget = new WindowTarget();
    gUIRoot->AddChild(gWindowTarget);
    gWindowTarget->SetVisible(false);

    SharedPtr<MilitaryPlant> militaryPlant = MilitaryPlant::Create();
    militaryPlant->SetCoord(Coord(0, 0));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void SceneRTS::Update(float /*timeStep*/)
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
void SceneRTS::HandleMouseDown(StringHash, VariantMap& eventData)
{
    int buttons = (int)eventData[MouseButtonDown::P_BUTTONS].GetInt();

    if(buttons == MOUSEB_LEFT)
    {
        ProcessMouseLeft();
    }
    else if(buttons == MOUSEB_RIGHT)
    {
        ProcessMouseRight();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void SceneRTS::ProcessMouseLeft()
{
    Vector3 hitCoord;
    Drawable *object = gCursor->GetRaycastNode(&hitCoord);

    if(!object)
    {
        return;
    }

    Node *node = object->GetNode();
    String name = node->GetName();

    if(name == NODE_TANK)
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
    else if(name == NODE_TERRAIN)
    {
        pathIndicator.Enable(true);
        Tank *tank = GetSelected();
        
        if(tank)
        {
            SetSelected(tank, false);
            tank->SetPath(pathIndicator.GetPath());
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void SceneRTS::ProcessMouseRight()
{
    pathIndicator.Enable(false);

    Drawable *object = gCursor->GetRaycastNode();

    if(object && object->GetNode()->GetName() == NODE_TANK)
    {
        object->GetNode()->GetComponent<Tank>()->EnableContextMenu();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void SceneRTS::SetSelected(Tank *tank_, bool selected)
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
    tank_->SetSelected(selected);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Tank* SceneRTS::GetSelected()
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

/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"
#include "Scene/_Scene.h"
#include "Core/_Math.h"
#include "Scene/Objects/Ammo/Rocket/Rocket.h"
#include "Scene/Objects/Buildings/MilitaryPlant/MilitaryPlant.h"
#include "Audio/Sounds.h"
#include "Game/Particles.h"
#include "GUI/GuiGame/WindowTarget.h"


SceneRTS::SceneRTS(Context *context, Mode _mode) : Object(context), mode(_mode)
{
    RegisterObjects();
}


SceneRTS::~SceneRTS()
{
    SAFE_DELETE(TheTerrain); //-V809
    pathIndicator.Stop();
}


void SceneRTS::RegisterObjects()
{
    Tank::RegisterObject();
    Rocket::RegisterObject();
    MilitaryPlant::RegisterObject();
}


void SceneRTS::RegisterObject(Context *context)
{
    context->RegisterFactory<SceneRTS>();
}


void SceneRTS::Create()
{
    Sounds::Init();

    Particles::Init();

    ThePhysicsWorld->SetFps(5);

    // Create a Zone component into a child scene node. The Zone controls ambient lighting and fog settings. Like the Octree,
    // it also defines its volume with a bounding box, but can be rotated (so it does not need to be aligned to the world X, Y
    // and Z axes.) Drawable objects "pick up" the zone they belong to and use it when rendering; several zones can exist

    Node* zoneNode = TheScene->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    // Set same volume as the Octree, set a close bluish fog and some ambient light
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetFogColor(Color::GRAY);
    zone->SetFogHeightScale(10000.0f);
    zone->SetFogStart(0.0f);
    zone->SetFogEnd(1000.0f);
    float dColor = 0.1f;
    zone->SetAmbientColor(Color(dColor, dColor, dColor));

    if(MODE_SERVER)
    {
        level = TheLevel->Load("Game/Levels/level.map");
    }
    else
    {
        level = TheLevel->Get();
    }

    TheTerrain = new TerrainRTS();
    TheTerrain->CreateFromVector(level);

    if (MODE_SERVER)
    {

        for (int i = 0; i < 5; i++)
        {
            uint row = 0;
            uint col = 0;
            do
            {
                col = static_cast<uint>(Math::RandomInt(0, static_cast<int>(TheLevel->GetWidth()) - 1));
                row = static_cast<uint>(Math::RandomInt(0, static_cast<int>(TheLevel->GetHeight()) - 1));
            } while (fabs(TheTerrain->GetHeight(row, col)) > M_EPSILON);

            SharedPtr<Tank> tank = Tank::Create(Tank::Small);
            tank->SetCoord({row, col});
            tank->SetAutoReloaded(1);
        }
    }

    SharedPtr<Node> lightNode;
    lightNode = TheScene->CreateChild("LigthNode");
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

    if (MODE_CLIENT)
    {
        TheRenderer->SetShadowMapSize(2048);
    }

    uint sizeX = level[0].Size();
    uint sizeZ = level.Size();

    TheCamera->SetPosition({sizeX / 2.0f, 25.0f, - static_cast<float>(sizeZ) / 2.0f - 10.0f}, {sizeX / 2.0f, 0.0f, -(sizeZ / 2.0f)});

    TheWindowTarget = new WindowTarget();
    TheUIRoot->AddChild(TheWindowTarget);
    TheWindowTarget->SetVisible(false);

    SharedPtr<MilitaryPlant> militaryPlant = MilitaryPlant::Create();
    militaryPlant->SetCoord(Coord(0, 0));

    pathIndicator.Init();

    SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(SceneRTS, HandleMouseDown));
}


void SceneRTS::Update(float /*timeStep*/)
{
    if (MODE_CLIENT)
    {
        Vector3 hitPos;
        Drawable *drawable = TheCursor->GetRaycastNode(&hitPos);

        if (drawable)
        {
            String name = drawable->GetNode()->GetName();
            if (name == NODE_TERRAIN)
            {
                TheCursor->SetNormal();
            }
            else if (name == NODE_TANK)
            {
                TheCursor->SetSelected();
            }
        }
        else
        {
            TheCursor->SetNormal();
        }

        pathIndicator.Update();
    }

    if (TheServer->IsRunning())
    {
        VectorBufferRTS msg;
        msg.WriteUInt(Tank::GetAll().Size());

        for (Tank *tank : Tank::GetAll())
        {
            msg.WriteTank(tank);
        }

        TheServer->SendToAll(MSG_SEND_SCREENSHOT, msg);
    }
}


void SceneRTS::HandleMouseDown(StringHash, VariantMap& eventData) //-V2009
{
    int buttons = static_cast<int>(eventData[MouseButtonDown::P_BUTTONS].GetInt());

    if(buttons == MOUSEB_LEFT)
    {
        ProcessMouseLeft();
    }
    else if(buttons == MOUSEB_RIGHT)
    {
        ProcessMouseRight();
    }
}


void SceneRTS::ProcessMouseLeft()
{
    Vector3 hitCoord;
    Drawable *object = TheCursor->GetRaycastNode(&hitCoord);

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
        Coord coord(static_cast<uint>(-position.z_), static_cast<uint>(position.x_)); //-V2004

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


void SceneRTS::ProcessMouseRight()
{
    pathIndicator.Enable(false);

    Drawable *object = TheCursor->GetRaycastNode();

    if(object && object->GetNode()->GetName() == NODE_TANK)
    {
        object->GetNode()->GetComponent<Tank>()->EnableContextMenu();
    }
}


void SceneRTS::SetSelected(Tank *tank_, bool selected)
{
    if(selected)
    {
        const Vector<SharedPtr<Node>> &nodes = TheScene->GetChildren();
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


Tank* SceneRTS::GetSelected()
{
    const Vector<SharedPtr<Node>> &nodes = TheScene->GetChildren();

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

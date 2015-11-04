#include <stdafx.h>


#include "Scene.h"
#include "Core/Camera.h"
#include "Core/Math.h"
#include "Game/Logic/Movinator.h"
#include "Game/Level.h"
#include "Game/Objects/Terrain.h"
#include "GUI/Elements/Cursor.h"
#include "Game/Path/TilePath.h"


Scene::Scene(UContext *context) :
    Object(context)
{
    RegisterObjects();

    Create();

    pathIndicator.Init();

    SubscribeToEvent(Urho3D::E_MOUSEBUTTONDOWN, HANDLER(Scene, HandleMouseDown));
}

void Scene::RegisterObjects()
{
    Tank::RegisterObject();
}

void Scene::RegisterObject(UContext *context)
{
    context->RegisterFactory<Scene>();
}

void Scene::Create()
{
    // Create a Zone component into a child scene node. The Zone controls ambient lighting and fog settings. Like the Octree,
    // it also defines its volume with a bounding box, but can be rotated (so it does not need to be aligned to the world X, Y
    // and Z axes.) UDrawable objects "pick up" the zone they belong to and use it when rendering; several zones can exist

    Node* zoneNode = gScene->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    // Set same volume as the Octree, set a close bluish fog and some ambient light
    zone->SetBoundingBox(UBoundingBox(-1000.0f, 1000.0f));
    //zone->SetFogColor(UColor::BLUE);
    //zone->SetFogHeightScale(10000.0f);
    //zone->SetFogStart(0.0f);
    //zone->SetFogEnd(1000.0f);
    float dColor = 0.1f;
    zone->SetAmbientColor(UColor(dColor, dColor, dColor));

    Vector<Vector<float>> level = gLevel->Load("TVData/Game/Levels/level.map");
    gTerrain = new Terrain(level);

    for (int i = 0; i < 100; i++)
    {
        int x = Math::RandomInt(0, (int)gLevel->GetWidth() - 1);
        int y = Math::RandomInt(0, (int)gLevel->GetHeight() - 1);

        for (auto tank : tanks)
        {
            Vector3 pos = tank->GetPosition();
            if ((int)pos.x_ == x && -(int)pos.z_ == y)
            {
                i--;
                continue;
            }
        }

        SharedPtr<Node> nodeTank(gScene->CreateChild(NODE_TANK));
        SharedPtr<Tank> tank(nodeTank->CreateComponent<Tank>());
        tank->Init(Tank::Small);
        tank->SetPosition({float(x), (float)gTerrain->GetHeight((uint)y, (uint)x), (float)-y});
    }

    SharedPtr<Node> lightNode;
    lightNode = gScene->CreateChild("LigthNode");
    Movinator *movinator = lightNode->CreateComponent<Movinator>();
    movinator->SetCenter({level[0].Size() / 2.0f, 25.0f, -(level.Size() / 2.0f)});
    movinator->SetMoveSpeed(0.5f);

    Light *light = lightNode->CreateComponent<Light>();
    lightNode->SetScale(0.01f);
    light->SetLightType(Urho3D::LIGHT_POINT);
    light->SetRange(1000.0f);
    light->SetCastShadows(true);
    light->SetShadowBias(Urho3D::BiasParameters(0.00025f, 0.5f));
    light->SetShadowCascade(UCascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetEnabled(true);
    gRenderer->SetShadowMapSize(2048);

    gCamera->SetPosition({0.0f, 25.0f, 0.0f}, {level[0].Size() / 2.0f, 0.0f, -(level.Size() / 2.0f)});
}

void Scene::Update()
{
    /*
    static Timer timer;
    if(timer.GetMSec(false) < 100)
    {
        return;
    }
    timer.Reset();
    */

    Vector3 hitPos;
    UDrawable *drawable = gCursor->GetRaycastNode(&hitPos);

    if (drawable)
    {
        pathIndicator.SetInCurrentCursorPosition(drawable, &hitPos);

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
}

void Scene::HandleMouseDown(StringHash, VariantMap& eventData)
{
    int buttons = (int)eventData[Urho3D::MouseButtonDown::P_BUTTONS].GetInt();

    if(buttons != Urho3D::MOUSEB_LEFT)
    {
        return;
    }

    pathIndicator.SetInCurrentCursorPosition();
}

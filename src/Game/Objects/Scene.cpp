#include <stdafx.h>


#include "Scene.h"
#include "Core/Camera.h"
#include "Core/Math.h"
#include "Game/Logic/Movinator.h"
#include "Game/Level.h"
#include "Game/Objects/Terrain.h"
#include "GUI/Elements/Cursor.h"


lScene::lScene(Context *context) :
    Object(context)
{
    Create();
}

void lScene::RegisterObject(Context *context)
{
    context->RegisterFactory<lScene>();
}

void lScene::Create()
{
    // Create a Zone component into a child scene node. The Zone controls ambient lighting and fog settings. Like the Octree,
    // it also defines its volume with a bounding box, but can be rotated (so it does not need to be aligned to the world X, Y
    // and Z axes.) Drawable objects "pick up" the zone they belong to and use it when rendering; several zones can exist

    Node* zoneNode = gScene->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    // Set same volume as the Octree, set a close bluish fog and some ambient light
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetFogColor(Color::BLUE);
    zone->SetFogHeightScale(10000.0f);
    zone->SetFogStart(0.0f);
    zone->SetFogEnd(1000.0f);
    float dColor = 0.1f;
    zone->SetAmbientColor(Color(dColor, dColor, dColor));

    Vector<Vector<float>> level = gLevel->Load("TVData/Game/Levels/level.map");
    gTerrain = new lTerrain(level);

    for (int i = 0; i < 1000; i++)
    {
        int x = Math::RandomInt(0, (int)gLevel->GetWidth() - 1);
        int y = Math::RandomInt(0, (int)gLevel->GetHeight() - 1);

        //if (!tanks.Empty())
        //{
            for (auto tank : tanks)
            {
                Vector3 pos = tank->GetPosition();
                if ((int)pos.x_ == x && -(int)pos.z_ == y)
                {
                    i--;
                    continue;
                }
            }
        //}

        SharedPtr<lTank> tank(new lTank(lTank::Small));
        tank->SetPosition({float(x), (float)gTerrain->GetHeight((uint)y, (uint)x), (float)-y});
        tanks.Push(tank);
    }

    SharedPtr<Node> lightNode;
    lightNode = gScene->CreateChild("LigthNode");
    vMovinator *movinator = lightNode->CreateComponent<vMovinator>();
    movinator->SetCenter({level[0].Size() / 2.0f, 25.0f, -(level.Size() / 2.0f)});
    movinator->SetMoveSpeed(0.5f);

    Light *light = lightNode->CreateComponent<Light>();
    lightNode->SetScale(0.01f);
    light->SetLightType(Urho3D::LIGHT_POINT);
    light->SetRange(1000.0f);
    light->SetCastShadows(true);
    light->SetShadowBias(Urho3D::BiasParameters(0.00025f, 0.5f));
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetEnabled(true);
    gRenderer->SetShadowMapSize(2048);

    gCamera->SetPosition({0.0f, 25.0f, 0.0f}, {level[0].Size() / 2.0f, 0.0f, -(level.Size() / 2.0f)});
}

bool lScene::Raycast(float maxDistance, Vector3 &hitPos, Drawable*& hitDrawable)
{
    hitDrawable = nullptr;

    IntVector2 pos = gCursor->GetCursor()->GetPosition();

    if (gUI->GetElementAt(pos, true))
    {
        return false;
    }

    Camera* camera = gCamera->GetNode()->GetComponent<Camera>();

    Ray ray = camera->GetScreenRay((float)pos.x_ / gGraphics->GetWidth(), (float)pos.y_ / gGraphics->GetHeight());
    PODVector<RayQueryResult> results;
    RayOctreeQuery query(results, ray, Urho3D::RAY_TRIANGLE, maxDistance, Urho3D::DRAWABLE_GEOMETRY);
    gScene->GetComponent<Octree>()->RaycastSingle(query);
    if (results.Size())
    {
        RayQueryResult& result = results[0];
        hitPos = result.position_;
        hitDrawable = result.drawable_;
        return true;
    }
    return false;
}

void lScene::Update()
{
    
    Vector3 hitPos;
    Drawable *hitDrawable;
    
    if (Raycast(1000.0f, hitPos, hitDrawable))
    {
        Node* node = hitDrawable->GetNode();
        node->GetName() == "Terrain" ? gCursor->SetNormal() : gCursor->SetSelected();
    }
    LOGINFOF
}

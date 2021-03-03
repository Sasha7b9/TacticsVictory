// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Core/Math_.h"
#include "Game/Logic/SunEngine_.h"
#include "Scene/Level_.h"
#include "Scene/Scene_.h"


SceneT::SceneT(Context *context) : Scene(context)
{

}


SceneT::~SceneT()
{
    delete TheTerrain;
}


void SceneT::RegisterComponent(Context *context)
{
    context->RegisterFactory<SceneT>();
}


void SceneT::Create()
{
    CreateComponent<Octree>(LOCAL);

    ThePhysicsWorld = CreateComponent<PhysicsWorld>(LOCAL);

    ThePhysicsWorld->SetGravity(Vector3::ZERO);

    ThePhysicsWorld->SetFps(5);

    // Create a Zone component into a child scene node. The Zone controls ambient lighting and fog settings. Like the Octree,
    // it also defines its volume with a bounding box, but can be rotated (so it does not need to be aligned to the world X, Y
    // and Z axes.) Drawable objects "pick up" the zone they belong to and use it when rendering; several zones can exist

    Node* zoneNode = CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>(LOCAL);
    // Set same volume as the Octree, set a close bluish fog and some ambient light
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetFogColor(Color::GRAY);
    zone->SetFogHeightScale(10000.0f);
    zone->SetFogStart(0.0f);
    zone->SetFogEnd(1000.0f);
    float dColor = 0.1f;
    zone->SetAmbientColor(Color(dColor, dColor, dColor));

    TheTerrain = new TerrainT();
    TheTerrain->CreateFromVector(TheLevel->map);

    SharedPtr<Node> lightNode;
    lightNode = CreateChild("LigthNode");
    SunEngine *sunEngine = lightNode->CreateComponent<SunEngine>(LOCAL);
    sunEngine->SetCenter({ TheLevel->map[0].Size() / 2.0f, 25.0f, TheLevel->map.Size() / 2.0f });
    sunEngine->SetMoveSpeed(0.5f);

    Light *light = lightNode->CreateComponent<Light>(LOCAL);
    lightNode->SetScale(0.01f);
    light->SetLightType(LIGHT_POINT);
    light->SetRange(1000.0f);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00011f, 2.0f));
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetEnabled(true);
}

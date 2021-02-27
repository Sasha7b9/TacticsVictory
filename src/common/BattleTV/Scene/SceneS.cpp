// 2021/02/27 19:34:10 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Level_.h"
#include "Scene/Scene_.h"


void SceneT::Create()
{
    ThePhysicsWorld->SetFps(5);

    // Create a Zone component into a child scene node. The Zone controls ambient lighting and fog settings. Like the Octree,
    // it also defines its volume with a bounding box, but can be rotated (so it does not need to be aligned to the world X, Y
    // and Z axes.) Drawable objects "pick up" the zone they belong to and use it when rendering; several zones can exist

    Node *zoneNode = CreateChild("Zone");
    float dColor = 0.1f;

    level = TheLevel->Load("Game/Levels/level.map");

    TheTerrain = new TTerrain();
    TheTerrain->CreateFromVector(level);

    SharedPtr<Node> lightNode;
    lightNode = CreateChild("LigthNode");

    Light *light = lightNode->CreateComponent<Light>();
    lightNode->SetScale(0.01f);
    light->SetLightType(LIGHT_POINT);
    light->SetRange(1000.0f);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00011f, 2.0f));
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetEnabled(true);
}

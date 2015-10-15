#include <stdafx.h>


tvScene::tvScene() :
    Object(gContext)
{
    Create();
}

void tvScene::Create()
{
    // Create a Zone component into a child scene node. The Zone controls ambient lighting and fog settings. Like the Octree,
    // it also defines its volume with a bounding box, but can be rotated (so it does not need to be aligned to the world X, Y
    // and Z axes.) Drawable objects "pick up" the zone they belong to and use it when rendering; several zones can exist

    Node* zoneNode = gScene->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    // Set same volume as the Octree, set a close bluish fog and some ambient light
    zone->SetBoundingBox(BoundingBox(-50.0f, 50.0f));
    //zone->SetFogColor(Color::WHITE);
    //zone->SetFogHeightScale(10.0f);
    //zone->SetFogStart(1.0f);
    //zone->SetFogEnd(500.0f);
    float dColor = 0.2f;
    zone->SetAmbientColor(Color(dColor, dColor, dColor));

    Vector<Vector<float> > level = Level::Load("input.txt");
    //Vector<Vector<float> > level = Level::CreateRandom(100, 100);

    SharedPtr<tvTerrainBlock> terrain;
    terrain = new tvTerrainBlock(level);

    SharedPtr<Node> lightNode;
    lightNode = gScene->CreateChild("LigthNode");
    tvMovinator *movinator = lightNode->CreateComponent<tvMovinator>();
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
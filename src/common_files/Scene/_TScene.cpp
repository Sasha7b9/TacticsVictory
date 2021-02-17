/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"


TScene::TScene(Context *context) : Object(context)
{
    scene = new Scene(context);

    RegisterObjects();
}


TScene::~TScene()
{
    delete scene;

    SAFE_DELETE(TheTerrain);
}


void TScene::RegisterObjects()
{
    STank::RegisterObject();
    CTank::RegisterObject();
    Rocket::RegisterObject();
    MilitaryPlant::RegisterObject();
}


void TScene::RegisterObject(Context *context)
{
    context->RegisterFactory<TScene>();
}


void TScene::Create()
{
    ThePhysicsWorld->SetFps(5);

    // Create a Zone component into a child scene node. The Zone controls ambient lighting and fog settings. Like the Octree,
    // it also defines its volume with a bounding box, but can be rotated (so it does not need to be aligned to the world X, Y
    // and Z axes.) Drawable objects "pick up" the zone they belong to and use it when rendering; several zones can exist

    Node* zoneNode = TheScene->scene->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    // Set same volume as the Octree, set a close bluish fog and some ambient light
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetFogColor(Color::GRAY);
    zone->SetFogHeightScale(10000.0f);
    zone->SetFogStart(0.0f);
    zone->SetFogEnd(1000.0f);
    float dColor = 0.1f;
    zone->SetAmbientColor(Color(dColor, dColor, dColor));

    level = TheLevel->Load("Game/Levels/level.map");

    TheTerrain = new TerrainTV();
    TheTerrain->CreateFromVector(level);

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
        tank->SetCoord({ row, col });
        tank->SetAutoReloaded(1);
    }

    SharedPtr<Node> lightNode;
    lightNode = TheScene->scene->CreateChild("LigthNode");
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
}


void TScene::Update(float timeStep)
{
    UNUSED(timeStep);
}


void TScene::SetSelected(Tank *tank_, bool selected)
{
    if(selected)
    {
        const Vector<SharedPtr<Node>> &nodes = TheScene->scene->GetChildren();
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


Tank* TScene::GetSelected()
{
    const Vector<SharedPtr<Node>> &nodes = TheScene->scene->GetChildren();

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

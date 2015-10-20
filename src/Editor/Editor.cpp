#include <stdafx.h>


#include "Editor.h"
#include "Core/Camera.h"
#include "Game/Level.h"
#include "GUI/Elements/Cursor.h"


lEditor::lEditor(Context *context) : Object(context)
{
    currentPlane = lPlane::ZERO;
}


void lEditor::Run()
{
    Node* zoneNode = gScene->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-50.0f, 50.0f));

    float dColor = 0.3f;
    zone->SetAmbientColor(Color(dColor, dColor, dColor));

    //Vector<Vector<float> > level = vLevel::CreateRandom(100, 100);
    Vector<Vector<float> > level = vLevel::Load("input.txt");

    terrain = new lTerrain(level);

    SharedPtr<Node> lightNode(gScene->CreateChild("LightNode"));

    SharedPtr<Light> light(lightNode->CreateComponent<Light>());
    lightNode->SetScale(0.01f);
    light->SetLightType(Urho3D::LIGHT_POINT);
    light->SetRange(100.0f);
    light->SetCastShadows(true);
    light->SetShadowBias(Urho3D::BiasParameters(0.00025f, 0.5f));
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetEnabled(true);
    gRenderer->SetShadowMapSize(2048);

    gCamera->SetPosition({0.0f, 25.0f, 0.0f}, {level[0].Size() / 2.0f, 0.0f, -(level.Size() / 2.0f)});
    lightNode->SetPosition({level[0].Size() / 2.0f, 50.0f, -(level.Size() / 2.0f)});

    SubscribeToEvent(E_POSTRENDERUPDATE, HANDLER(lEditor, HandlePostRenderUpdate));
}

void lEditor::HandlePostRenderUpdate(StringHash, VariantMap &eventData)
{
    IntVector2 pos = gCursor->GetCursor()->GetPosition();

    float relX = (float)pos.x_ / gGraphics->GetWidth();
    float relY = (float)pos.y_ / gGraphics->GetHeight();

    Ray ray = gCamera->GetNode()->GetComponent<Camera>()->GetScreenRay(relX, relY);

    lPlane plane = terrain->GetIntersection(ray);

    if(!plane.IsZero())
    {
        currentPlane = plane;
        Color color = (int)(gTime->GetElapsedTime() * 10.0f) % 4 < 2 ? Color::CYAN : Color::BLUE;
        gDebugRenderer->AddTriangle(currentPlane.v0, currentPlane.v1, currentPlane.v2, color, true);
        gDebugRenderer->AddTriangle(currentPlane.v0, currentPlane.v2, currentPlane.v3, color, true);
    }

    float deltaStep = (float)eventData[Urho3D::PostRenderUpdate::P_TIMESTEP].GetFloat();

    static float currentHeight = 0.0f;

    currentHeight += deltaStep * 10.0f;

    terrain->SetHeight(5, 5, currentHeight);
}
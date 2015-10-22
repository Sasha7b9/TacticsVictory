#include <stdafx.h>


#include "Editor.h"
#include "Core/Camera.h"
#include "Game/Level.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/Elements/Hint.h"
#include "GUI/GUI.h"
#include "GUI/GuiEditor/GuiEditor.h"


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

    //Vector<Vector<float> > level = gLevel->CreateRandom(100, 100);
    Vector<Vector<float> > level = gLevel->Load("input.txt");

    gTerrain = new lTerrain(level);

    SharedPtr<Node> lightNode(gScene->CreateChild("LightNode"));

    SharedPtr<Light> light(lightNode->CreateComponent<Light>());
    lightNode->SetScale(0.01f);
    light->SetLightType(Urho3D::LIGHT_POINT);
    light->SetRange(100.0f);
    light->SetCastShadows(true);
    light->SetShadowBias(Urho3D::BiasParameters(0.00025f, 0.5f));
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetEnabled(true);

    gCamera->SetPosition({0.0f, 25.0f, 0.0f}, {level[0].Size() / 2.0f, 0.0f, -(level.Size() / 2.0f)});
    lightNode->SetPosition({level[0].Size() / 2.0f, 50.0f, -(level.Size() / 2.0f)});

    SubscribeToEvent(Urho3D::E_POSTRENDERUPDATE, HANDLER(lEditor, HandlePostRenderUpdate));
    SubscribeToEvent(Urho3D::E_KEYDOWN, HANDLER(lEditor, HandleKeyDown));
    SubscribeToEvent(Urho3D::E_MOUSEBUTTONDOWN, HANDLER(lEditor, HandleMouseDown));
}

void lEditor::HandlePostRenderUpdate(StringHash, VariantMap &)
{
    if (gTerrain->Empty())
    {
        return;
    }
    if (!gGUI->MenuIsVisible() && !gGUI->UnderCursor())
    {
        IntVector2 pos = gCursor->GetCursor()->GetPosition();

        float relX = (float)pos.x_ / gGraphics->GetWidth();
        float relY = (float)pos.y_ / gGraphics->GetHeight();

        Ray ray = gCamera->GetNode()->GetComponent<Camera>()->GetScreenRay(relX, relY);

        lPlane plane = gTerrain->GetIntersection(ray);

        if (!plane.IsZero())
        {
            currentPlane = plane;
            Color color = (int)(gTime->GetElapsedTime() * 10.0f) % 4 < 2 ? Color::CYAN : Color::BLUE;
            gDebugRenderer->AddTriangle(currentPlane.v0, currentPlane.v1, currentPlane.v2, color, true);
            gDebugRenderer->AddTriangle(currentPlane.v0, currentPlane.v2, currentPlane.v3, color, true);
        }
    }

    /*
    float deltaStep = (float)eventData[Urho3D::PostRenderUpdate::P_TIMESTEP].GetFloat();

    static float currentHeight = 0.0f;

    currentHeight += deltaStep * 10.0f;

    gTerrain->SetHeight(5, 5, currentHeight);
    */
}

void lEditor::HandleKeyDown(StringHash, VariantMap& eventData)
{
    int key = eventData[Urho3D::KeyDown::P_KEY].GetInt();

    if (key == Urho3D::KEY_P)
    {
        gGuiEditor->TogglePanelMain();
    }
    else if (key == Urho3D::KEY_M)
    {
        gGuiEditor->TogglePanelMap();
    }
}

void lEditor::HandleMouseDown(StringHash, VariantMap&)
{
    if(gHint && gCounterHint != 0)
    {
        gUIRoot->RemoveChild(gHint);
        gHint = nullptr;
    }
    gCounterHint++;
}


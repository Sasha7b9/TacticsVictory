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
    selectedPlane = lPlane::ZERO;
}


void lEditor::Run()
{
    Node* zoneNode = gScene->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-50.0f, 50.0f));

    float dColor = 0.3f;
    zone->SetAmbientColor(Color(dColor, dColor, dColor));

    //Vector<Vector<float> > level = gLevel->CreateRandom(100, 100);
    Vector<Vector<float> > level = gLevel->Load("input.map");

    gTerrain = new lTerrain(level);

    lightNode = gScene->CreateChild("LightNode");

    SharedPtr<Light> light(lightNode->CreateComponent<Light>());
    lightNode->SetScale(0.01f);
    light->SetLightType(Urho3D::LIGHT_POINT);
    light->SetRange(100.0f);
    light->SetCastShadows(true);
    light->SetShadowBias(Urho3D::BiasParameters(0.00025f, 0.5f));
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetEnabled(true);

    gCamera->SetPosition({10.0f, 20.0f, -5.0f}, {10.0f, 0.0f, 0.0f});
    lightNode->SetPosition({level[0].Size() / 2.0f, 50.0f, -(level.Size() / 2.0f)});

    SubscribeToEvent(Urho3D::E_POSTRENDERUPDATE, HANDLER(lEditor, HandlePostRenderUpdate));
    SubscribeToEvent(Urho3D::E_MOUSEBUTTONDOWN, HANDLER(lEditor, HandleMouseDown));
    SubscribeToEvent(Urho3D::E_KEYDOWN, HANDLER(lEditor, HandleKeyDown));
}

void lEditor::ClearScene()
{
    SAFE_DELETE(gTerrain);
    gScene->RemoveChild(lightNode);
}

void lEditor::HandlePostRenderUpdate(StringHash, VariantMap &)
{
    if (!gTerrain || gTerrain->Empty())
    {
        return;
    }

    if(!selectedPlane.IsZero())
    {
        Color color = Color::BLUE;
        gDebugRenderer->AddTriangle(selectedPlane.v0, selectedPlane.v1, selectedPlane.v2, color, false);
        gDebugRenderer->AddTriangle(selectedPlane.v0, selectedPlane.v2, selectedPlane.v3, color, false);
    }

    if (!gGUI->MenuIsVisible() && !gGUI->UnderCursor() && !gInput->GetMouseButtonDown(Urho3D::MOUSEB_RIGHT | Urho3D::MOUSEB_MIDDLE))
    {
        IntVector2 pos = gCursor->GetCursor()->GetPosition();

        float relX = (float)pos.x_ / gGraphics->GetWidth();
        float relY = (float)pos.y_ / gGraphics->GetHeight();

        Ray ray = gCamera->GetNode()->GetComponent<Camera>()->GetScreenRay(relX, relY);

        currentPlane = gTerrain->GetIntersection(ray);

        if (!currentPlane.IsZero() && (gCursor->GetType() == TypeCursor_Normal || gCursor->GetType() == TypeCursor_Selected))
        {
            if(!selectedPlane.IsEquals(currentPlane))
            {
                Color color = (int)(gTime->GetElapsedTime() * 10.0f) % 4 < 2 ? Color::CYAN : Color::BLUE;
                gDebugRenderer->AddTriangle(currentPlane.v0, currentPlane.v1, currentPlane.v2, color, true);
                gDebugRenderer->AddTriangle(currentPlane.v0, currentPlane.v2, currentPlane.v3, color, true);
            }
            gCursor->SetSelected();
        }
        else
        {
            gCursor->SetNormal();
        }
    }

    /*
    float deltaStep = (float)eventData[Urho3D::PostRenderUpdate::P_TIMESTEP].GetFloat();

    static float currentHeight = 0.0f;

    currentHeight += deltaStep * 10.0f;

    gTerrain->SetHeight(5, 5, currentHeight);
    */
}

void lEditor::HandleMouseDown(StringHash, VariantMap&)
{
    if(gHint && gCounterHint != 0)
    {
        gUIRoot->RemoveChild(gHint);
        gHint = nullptr;
    }
    gCounterHint++;

    if(gInput->GetMouseButtonDown(Urho3D::MOUSEB_LEFT) && !gInput->GetMouseButtonDown(Urho3D::MOUSEB_MIDDLE) && !gInput->GetMouseButtonDown(Urho3D::MOUSEB_RIGHT))
    {
        selectedPlane = lPlane::ZERO;

        if(!currentPlane.IsZero())
        {
            selectedPlane = currentPlane;
            selectedPlane.CalculateRowCol();
        }
    }
}

void lEditor::HandleKeyDown(StringHash, VariantMap& eventData)
{
    int key = eventData[Urho3D::KeyDown::P_KEY].GetInt();

    if(!selectedPlane.IsZero())
    {
        uint row = selectedPlane.row;
        uint col = selectedPlane.col;
        int height = gTerrain->GetHeight(row, col);
        if(key == Urho3D::KEY_KP_MINUS)
        {
            gTerrain->SetHeight(row, col, height - 1.0f);
            gTerrain->Update();
        }
        else if(key == Urho3D::KEY_KP_PLUS)
        {
            gTerrain->SetHeight(row, col, height + 1.0f);
            gTerrain->Update();
        }
        height = gTerrain->GetHeight(row, col) + 0.2f;
        selectedPlane.SetY(height);
    }
}

#include <stdafx.h>


#include "Editor.h"
#include "Core/Camera.h"
#include "Game/Level.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/Elements/Hint.h"
#include "GUI/GUI.h"
#include "GUI/GuiEditor/GuiEditor.h"
#include "Game/Objects/Units/Tank/Tank.h"


Editor::Editor(Context *context) : Object(context)
{
    currentPlane = PlaneRTS::ZERO;
    selectedPlane = PlaneRTS::ZERO;
}


void Editor::Run()
{
    Node* zoneNode = gScene->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-50.0f, 50.0f));

    float dColor = 0.3f;
    zone->SetAmbientColor(Color(dColor, dColor, dColor));

    Vector<Vector<float>> level = gLevel->Load("Game/Levels/level.map");

    gTerrain = new TerrainRTS();
    gTerrain->CreateFromVector(level);

    lightNode = gScene->CreateChild("LightNode");

    SharedPtr<Light> light(lightNode->CreateComponent<Light>());
    lightNode->SetScale(0.01f);
    light->SetLightType(LIGHT_POINT);
    light->SetRange(1000.0f);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetEnabled(true);

    gCamera->SetPosition({(float)gTerrain->NumCols() / 2, 5.0f, -(float)gTerrain->NumRows() / 2 - 10.0f}, {(float)gTerrain->NumCols() / 2, 0.0f, -(float)gTerrain->NumRows() / 2});
    lightNode->SetPosition({(float)gTerrain->NumCols() / 2, 50.0f, -(float)gTerrain->NumRows() / 2});

    SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(Editor, HandlePostRenderUpdate));
    SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(Editor, HandleMouseDown));
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(Editor, HandleKeyDown));
    
    /*
    for(uint row = 0; row < 10; row++)
    {
        for(uint col = 0; col < 10; col++)
        {
            SharedPtr<Tank> tank(new Tank());
            tank->Init(Tank::Small);
            tank->SetPosition(Vector3(float(col), gTerrain->GetHeight(row, col), -float(row)));
        }
    }
    */

    /*
    Node* modelNode = gScene->CreateChild("Tank");
    modelNode->SetPosition({4.5f, 0.5f, -5.0f});
    modelNode->SetScale(0.15f);
    StaticModel *modelObject = modelNode->CreateComponent<StaticModel>();
    modelObject->SetModel(gCache->GetResource<Model>("Models/T-34-76-2.mdl"));
    //modelObject->SetMaterial(gCache->GetResource<Material>("Materials/T-34-76-2_05.xml"));
    modelObject->SetCastShadows(true);
    */
}

void Editor::ClearScene()
{
    SAFE_DELETE(gTerrain);
    gScene->RemoveChild(lightNode);
}

void Editor::HandlePostRenderUpdate(StringHash, VariantMap &)
{
    if (!gTerrain || gTerrain->Empty())
    {
        return;
    }

    IntVector2 pos = gCursor->GetCursor()->GetPosition();

    float relX = (float)pos.x_ / gGraphics->GetWidth();
    float relY = (float)pos.y_ / gGraphics->GetHeight();

    Ray ray = gCamera->GetNode()->GetComponent<Camera>()->GetScreenRay(relX, relY);

    if (gGuiEditor->modeSelect == GuiEditor::ModeSelect_Plane)
    {
        if (!selectedPlane.IsZero())
        {
            Color color = Color::BLUE;
            gDebugRenderer->AddTriangle(selectedPlane.v0, selectedPlane.v1, selectedPlane.v2, color, false);
            gDebugRenderer->AddTriangle(selectedPlane.v0, selectedPlane.v2, selectedPlane.v3, color, false);
        }

        if (!gGUI->MenuIsVisible() && !gGUI->UnderCursor() && !gInput->GetMouseButtonDown(MOUSEB_RIGHT | MOUSEB_MIDDLE))
        {
            Timer timer;
            currentPlane = gTerrain->GetIntersectionPlane(ray);

            if (!currentPlane.IsZero() && (gCursor->GetType() == TypeCursor_Normal || gCursor->GetType() == TypeCursor_Selected))
            {
                if (!selectedPlane.IsEquals(currentPlane))
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
    }

    if (gGuiEditor->modeSelect == GuiEditor::ModeSelect_Edge)
    {
        if (!gGUI->MenuIsVisible() && !gGUI->UnderCursor() && !gInput->GetMouseButtonDown(MOUSEB_RIGHT | MOUSEB_MIDDLE))
        {
            currentEdge = gTerrain->GetIntersectionEdge(ray);

            if (!currentEdge.IsZero() && (gCursor->GetType() == TypeCursor_Normal || gCursor->GetType() == TypeCursor_Selected))
            {
                Color color = (int)(gTime->GetElapsedTime() * 10.0f) % 4 < 2 ? Color::CYAN : Color::BLUE;

                float dX = fabs(currentEdge.start.x_ - currentEdge.end.x_);
                float dZ = fabs(currentEdge.start.z_ - currentEdge.end.z_);

                gDebugRenderer->AddLine(currentEdge.start, currentEdge.end, color, false);

                float d = 0.005f;
                int numLines = 20;

                if (dZ > dX)
                {
                    for (int i = 0; i < numLines; i++)
                    {
                        gDebugRenderer->AddLine(currentEdge.start + Vector3(d * i - d * numLines / 2, 0.0f, 0.0f), currentEdge.end + Vector3(d * i - d * numLines / 2, 0.0f, 0.0f), color, false);
                    }
                }
                else
                {
                    for (int i = 0; i < numLines; i++)
                    {
                        gDebugRenderer->AddLine(currentEdge.start + Vector3(0.0f, 0.0f, d * i - d * numLines / 2), currentEdge.end + Vector3(0.0f, 0.0f, d * i - d * numLines / 2), color, false);
                    }
                }
            }
            gCursor->SetSelected();
        }
        else
        {
            gCursor->SetNormal();
        }
    }

    /*
    float deltaStep = (float)eventData[PostRenderUpdate::P_TIMESTEP].GetFloat();

    static float currentHeight = 0.0f;

    currentHeight += deltaStep * 10.0f;

    gTerrain->SetHeight(5, 5, currentHeight);
    */
}

void Editor::HandleMouseDown(StringHash, VariantMap&)
{
    if (gHint && gCounterHint != 0)
    {
        gUIRoot->RemoveChild(gHint);
        gHint = nullptr;
    }
    gCounterHint++;

    if (gGUI->UnderCursor())
    {
        return;
    }

    if (gGuiEditor->modeSelect == GuiEditor::ModeSelect_Plane)
    {
        if (gInput->GetMouseButtonDown(MOUSEB_LEFT) && !gInput->GetMouseButtonDown(MOUSEB_MIDDLE) && !gInput->GetMouseButtonDown(MOUSEB_RIGHT))
        {
            if (!selectedPlane.IsEquals(PlaneRTS::ZERO) && selectedPlane.IsEquals(currentPlane))
            {
                selectedPlane = PlaneRTS::ZERO;
                gCamera->EnableArrows();
            }
            else
            {
                selectedPlane = PlaneRTS::ZERO;
                gCamera->EnableArrows();

                if (!currentPlane.IsZero())
                {
                    selectedPlane = currentPlane;
                    selectedPlane.CalculateRowCol();
                    gCamera->DisableArrows();
                }
            }
        }
    }
}

void Editor::HandleKeyDown(StringHash, VariantMap& eventData)
{
    int key = eventData[KeyDown::P_KEY].GetInt();

    if(!selectedPlane.IsZero())
    {
        uint row = selectedPlane.row;
        uint col = selectedPlane.col;
        float height = gTerrain->GetHeight(row, col);
        if(key == KEY_KP_MINUS)
        {
            gTerrain->SetHeight(row, col, height - 1.0f);
            gTerrain->Update();
        }
        else if(key == KEY_KP_PLUS)
        {
            gTerrain->SetHeight(row, col, height + 1.0f);
            gTerrain->Update();
        }
        selectedPlane = gTerrain->GetPlane(row, col);

        if (key == KEY_LEFT)
        {
            if (col > 0)
            {
                selectedPlane = gTerrain->GetPlane(row, col - 1);
            }
        }
        else if (key == KEY_RIGHT)
        {
            if (col < gLevel->GetWidth() - 1)
            {
                selectedPlane = gTerrain->GetPlane(row, col + 1);
            }
        }
        else if (key == KEY_UP)
        {
            if (row > 0)
            {
                selectedPlane = gTerrain->GetPlane(row - 1, col);
            }
        }
        else if (key == KEY_DOWN)
        {
            if (row < gLevel->GetHeight() - 1)
            {
                selectedPlane = gTerrain->GetPlane(row + 1, col);
            }
        }
    }
}

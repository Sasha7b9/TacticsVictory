/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include <stdafx.h>
#include "Core/Camera.h"
#include "Editor.h"
#include "Game/Level.h"
#include "Game/Objects/Units/Tank/Tank.h"
#include "GUI/Cursor.h"
#include "GUI/Controls/Hint.h"
#include "GUI/GUI.h"
#include "GUI/GuiEditor/GuiEditor.h"
#include "GUI/Menu/MenuRTS.h"



Editor::Editor(Context *context) : Object(context)
{
    currentPlane = PlaneRTS::ZERO;
    selectedPlane = PlaneRTS::ZERO;
}



void Editor::Run()
{
    Node* zoneNode = TheScene->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-50.0f, 50.0f));

    float dColor = 0.3f;
    zone->SetAmbientColor(Color(dColor, dColor, dColor));

    Vector<Vector<float>> level = gLevel->Load("Game/Levels/level.map");

    gTerrain = new TerrainRTS();
    gTerrain->CreateFromVector(level);

    lightNode = TheScene->CreateChild("LightNode");

    SharedPtr<Light> light(lightNode->CreateComponent<Light>());
    lightNode->SetScale(0.01f);
    light->SetLightType(LIGHT_POINT);
    light->SetRange(1000.0f);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetEnabled(true);

    gCamera->SetPosition({gTerrain->NumCols() / 2.0f, 5.0f, - static_cast<float>(gTerrain->NumRows()) / 2.0f - 10.0f}, {gTerrain->NumCols() / 2.0f, 0.0f, - static_cast<float>(gTerrain->NumRows()) / 2.0f});
    lightNode->SetPosition({gTerrain->NumCols() / 2.0f, 50.0f, - static_cast<float>(gTerrain->NumRows()) / 2.0f});

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
    Node* modelNode = TheScene->CreateChild("Tank");
    modelNode->SetPosition({4.5f, 0.5f, -5.0f});
    modelNode->SetScale(0.15f);
    StaticModel *modelObject = modelNode->CreateComponent<StaticModel>();
    modelObject->SetModel(TheCache->GetResource<Model>("Models/T-34-76-2.mdl"));
    //modelObject->SetMaterial(TheCache->GetResource<Material>("Materials/T-34-76-2_05.xml"));
    modelObject->SetCastShadows(true);
    */
}


void Editor::ClearScene()
{
    SAFE_DELETE(gTerrain); //-V809
    TheScene->RemoveChild(lightNode);
}


void Editor::HandlePostRenderUpdate(StringHash, VariantMap &)
{
    if (!gTerrain || gTerrain->Empty())
    {
        return;
    }

    IntVector2 pos = gCursor->GetCursor()->GetPosition();

    float relX = static_cast<float>(pos.x_) / TheGraphics->GetWidth();
    float relY = static_cast<float>(pos.y_) / TheGraphics->GetHeight();

    Ray ray = gCamera->GetNode()->GetComponent<Camera>()->GetScreenRay(relX, relY);

    if (gGuiEditor->modeSelect == GuiEditor::ModeSelect_Plane)
    {
        if (!selectedPlane.IsZero())
        {
            Color color = Color::BLUE;
            TheDebugRenderer->AddTriangle(selectedPlane.v0, selectedPlane.v1, selectedPlane.v2, color, false);
            TheDebugRenderer->AddTriangle(selectedPlane.v0, selectedPlane.v2, selectedPlane.v3, color, false);
        }

        if (!gMenu->IsActive() && !gGUI->UnderCursor() && !TheInput->GetMouseButtonDown(MOUSEB_RIGHT | MOUSEB_MIDDLE))
        {
            Timer timer;
            currentPlane = gTerrain->GetIntersectionPlane(ray);

            if (!currentPlane.IsZero() && (gCursor->GetType() == TypeCursor_Normal || gCursor->GetType() == TypeCursor_Selected))
            {
                if (!selectedPlane.IsEquals(currentPlane))
                {
                    Color color = static_cast<int>(TheTime->GetElapsedTime() * 10.0f) % 4 < 2 ? Color::CYAN : Color::BLUE; //-V112
                    TheDebugRenderer->AddTriangle(currentPlane.v0, currentPlane.v1, currentPlane.v2, color, true);
                    TheDebugRenderer->AddTriangle(currentPlane.v0, currentPlane.v2, currentPlane.v3, color, true);
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
        if (!gMenu->IsActive() && !gGUI->UnderCursor() && !TheInput->GetMouseButtonDown(MOUSEB_RIGHT | MOUSEB_MIDDLE))
        {
            currentEdge = gTerrain->GetIntersectionEdge(ray);

            if (!currentEdge.IsZero() && (gCursor->GetType() == TypeCursor_Normal || gCursor->GetType() == TypeCursor_Selected))
            {
                Color color = static_cast<int>(TheTime->GetElapsedTime() * 10.0f) % 4 < 2 ? Color::CYAN : Color::BLUE; //-V112

                float dX = fabs(currentEdge.start.x_ - currentEdge.end.x_);
                float dZ = fabs(currentEdge.start.z_ - currentEdge.end.z_);

                TheDebugRenderer->AddLine(currentEdge.start, currentEdge.end, color, false);

                float d = 0.005f;
                int numLines = 20;

                if (dZ > dX)
                {
                    for (int i = 0; i < numLines; i++)
                    {
                        TheDebugRenderer->AddLine(currentEdge.start + Vector3(d * i - d * numLines / 2, 0.0f, 0.0f), currentEdge.end + Vector3(d * i - d * numLines / 2, 0.0f, 0.0f), color, false);
                    }
                }
                else
                {
                    for (int i = 0; i < numLines; i++)
                    {
                        TheDebugRenderer->AddLine(currentEdge.start + Vector3(0.0f, 0.0f, d * i - d * numLines / 2), currentEdge.end + Vector3(0.0f, 0.0f, d * i - d * numLines / 2), color, false);
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
        TheUIRoot->RemoveChild(gHint);
        gHint = nullptr;
    }
    gCounterHint++;

    if (gGUI->UnderCursor())
    {
        return;
    }

    if (gGuiEditor->modeSelect == GuiEditor::ModeSelect_Plane)
    {
        if (TheInput->GetMouseButtonDown(MOUSEB_LEFT) && !TheInput->GetMouseButtonDown(MOUSEB_MIDDLE) && !TheInput->GetMouseButtonDown(MOUSEB_RIGHT))
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


void Editor::HandleKeyDown(StringHash, VariantMap& eventData) //-V2009
{
    int key = eventData[KeyDown::P_KEY].GetInt();

    if(!selectedPlane.IsZero())
    {
        uint row = selectedPlane.row;
        uint col = selectedPlane.col;
        float height = gTerrain->GetHeight(row, col);
        if(KEY_IS_KP_MINUS)
        {
            gTerrain->SetHeight(row, col, height - 1.0f);
            gTerrain->Update();
        }
        else if(KEY_IS_KP_PLUS)
        {
            gTerrain->SetHeight(row, col, height + 1.0f);
            gTerrain->Update();
        }
        selectedPlane = gTerrain->GetPlane(row, col);

        if (KEY_IS_LEFT)
        {
            if (col > 0)
            {
                selectedPlane = gTerrain->GetPlane(row, col - 1);
            }
        }
        else if (KEY_IS_RIGHT)
        {
            if (col < gLevel->GetWidth() - 1)
            {
                selectedPlane = gTerrain->GetPlane(row, col + 1);
            }
        }
        else if (KEY_IS_UP)
        {
            if (row > 0)
            {
                selectedPlane = gTerrain->GetPlane(row - 1, col);
            }
        }
        else if (KEY_IS_DOWN)
        {
            if (row < gLevel->GetHeight() - 1)
            {
                selectedPlane = gTerrain->GetPlane(row + 1, col);
            }
        }
    }
}

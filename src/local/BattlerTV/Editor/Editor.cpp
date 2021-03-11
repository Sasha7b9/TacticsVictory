// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Editor/Editor.h"
#include "GUI/Cursor.h"
#include "GUI/GUI.h"
#include "GUI/Controls/Hint_.h"
#include "GUI/GuiEditor/GuiEditor.h"
#include "GUI/Menu/Menu.h"
#include "Scene/Level_.h"
#include "Scene/SceneC.h"
#include "Scene/Cameras/Camera.h"


Editor::Editor(Context *context) : Object(context)
{
    currentPlane = TPlane::ZERO;
    selectedPlane = TPlane::ZERO;
}


void Editor::Run()
{
    Node* zoneNode = TheScene->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>(LOCAL);
    zone->SetBoundingBox(BoundingBox(-50.0f, 50.0f));

    float dColor = 0.3f;
    zone->SetAmbientColor(Color(dColor, dColor, dColor));

    TheLevel->Load("Game/Levels/level.map");

    TheTerrain = new TerrainT();
    TheTerrain->CreateFromVector(TheLevel->map);

    lightNode = TheScene->CreateChild("LightNode");

    SharedPtr<Light> light(lightNode->CreateComponent<Light>(LOCAL));
    lightNode->SetScale(0.01f);
    light->SetLightType(LIGHT_POINT);
    light->SetRange(1000.0f);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetEnabled(true);

    TheCamera->SetPosition(
        {TheTerrain->WidthZ() / 2.0f, 5.0f, - static_cast<float>(TheTerrain->HeightX()) / 2.0f - 10.0f},
        {TheTerrain->WidthZ() / 2.0f, 0.0f, - static_cast<float>(TheTerrain->HeightX()) / 2.0f});
    lightNode->SetPosition({TheTerrain->WidthZ() / 2.0f, 50.0f, - static_cast<float>(TheTerrain->HeightX()) / 2.0f});

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
            tank->SetPosition(Vector3(float(col), TheTerrain->GetHeight(row, col), -float(row)));
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
    delete TheTerrain;
    TheScene->RemoveChild(lightNode);
}


void Editor::HandlePostRenderUpdate(StringHash, VariantMap &)
{
    if (!TheTerrain || TheTerrain->IsEmpty())
    {
        return;
    }

    IntVector2 pos = TheCursor->GetCursor()->GetPosition();

    float relX = static_cast<float>(pos.x_) / TheGraphics->GetWidth();
    float relY = static_cast<float>(pos.y_) / TheGraphics->GetHeight();

    Ray ray = TheCamera->GetNode()->GetComponent<Camera>()->GetScreenRay(relX, relY);

    if (TheGuiEditor->modeSelect == GuiEditor::ModeSelect_Plane)
    {
        if (!selectedPlane.IsZero())
        {
            Color color = Color::BLUE;
            TheDebugRenderer->AddTriangle(selectedPlane.v0, selectedPlane.v1, selectedPlane.v2, color, false);
            TheDebugRenderer->AddTriangle(selectedPlane.v0, selectedPlane.v2, selectedPlane.v3, color, false);
        }

        if (!TheMenu->IsActive() &&
            !TheGUI->UnderCursor() &&
            !TheInput->GetMouseButtonDown(MOUSEB_RIGHT | MOUSEB_MIDDLE))
        {
            Timer timer;
            currentPlane = TheTerrain->GetIntersectionPlane(ray);

            if (!currentPlane.IsZero() &&
                (TheCursor->GetType() == CursorT::Type::Normal || TheCursor->GetType() == CursorT::Type::Selected))
            {
                if (!selectedPlane.IsEquals(currentPlane))
                {
                    Color color = static_cast<int>
                        (TheTime->GetElapsedTime() * 10.0f) % 4 < 2 ? Color::CYAN : Color::BLUE; //-V112

                    TheDebugRenderer->AddTriangle(currentPlane.v0, currentPlane.v1, currentPlane.v2, color, true);
                    TheDebugRenderer->AddTriangle(currentPlane.v0, currentPlane.v2, currentPlane.v3, color, true);
                }
                TheCursor->SetSelected();
            }
            else
            {
                TheCursor->SetNormal();
            }
        }
    }

    if (TheGuiEditor->modeSelect == GuiEditor::ModeSelect_Edge)
    {
        if (!TheMenu->IsActive() &&
            !TheGUI->UnderCursor() &&
            !TheInput->GetMouseButtonDown(MOUSEB_RIGHT | MOUSEB_MIDDLE))
        {
            currentEdge = TheTerrain->GetIntersectionEdge(ray);

            if (!currentEdge.IsZero() &&
                (TheCursor->GetType() == CursorT::Type::Normal || TheCursor->GetType() == CursorT::Type::Selected))
            {
                Color color = static_cast<int>
                    (TheTime->GetElapsedTime() * 10.0f) % 4 < 2 ? Color::CYAN : Color::BLUE; //-V112

                float dX = fabs(currentEdge.start.x_ - currentEdge.end.x_);
                float dZ = fabs(currentEdge.start.z_ - currentEdge.end.z_);

                TheDebugRenderer->AddLine(currentEdge.start, currentEdge.end, color, false);

                float d = 0.005f;
                int numLines = 20;

                if (dZ > dX)
                {
                    for (int i = 0; i < numLines; i++)
                    {
                        TheDebugRenderer->AddLine(currentEdge.start + Vector3(d * i - d * numLines / 2, 0.0f, 0.0f),
                            currentEdge.end + Vector3(d * i - d * numLines / 2, 0.0f, 0.0f), color, false);
                    }
                }
                else
                {
                    for (int i = 0; i < numLines; i++)
                    {
                        TheDebugRenderer->AddLine(currentEdge.start + Vector3(0.0f, 0.0f, d * i - d * numLines / 2),
                            currentEdge.end + Vector3(0.0f, 0.0f, d * i - d * numLines / 2), color, false);
                    }
                }
            }
            TheCursor->SetSelected();
        }
        else
        {
            TheCursor->SetNormal();
        }
    }

    /*
    float deltaStep = (float)eventData[PostRenderUpdate::P_TIMESTEP].GetFloat();

    static float currentHeight = 0.0f;

    currentHeight += deltaStep * 10.0f;

    TheTerrain->SetHeight(5, 5, currentHeight);
    */
}


void Editor::HandleMouseDown(StringHash, VariantMap&)
{
    if (TheGUI->UnderCursor())
    {
        return;
    }

    if (TheGuiEditor->modeSelect == GuiEditor::ModeSelect_Plane)
    {
        if (TheInput->GetMouseButtonDown(MOUSEB_LEFT) &&
            !TheInput->GetMouseButtonDown(MOUSEB_MIDDLE) &&
            !TheInput->GetMouseButtonDown(MOUSEB_RIGHT))
        {
            if (!selectedPlane.IsEquals(TPlane::ZERO) && selectedPlane.IsEquals(currentPlane))
            {
                selectedPlane = TPlane::ZERO;
                TheCamera->EnableArrows();
            }
            else
            {
                selectedPlane = TPlane::ZERO;
                TheCamera->EnableArrows();

                if (!currentPlane.IsZero())
                {
                    selectedPlane = currentPlane;
                    selectedPlane.CalculateRowCol();
                    TheCamera->DisableArrows();
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
        float height = TheTerrain->_GetHeight(row, col);
        if(KEY_IS_KP_MINUS)
        {
            TheTerrain->SetHeight(row, col, height - 1.0f);
        }
        else if(KEY_IS_KP_PLUS)
        {
            TheTerrain->SetHeight(row, col, height + 1.0f);
        }
        selectedPlane = TheTerrain->GetPlane(row, col);

        if (KEY_IS_LEFT)
        {
            if (col > 0)
            {
                selectedPlane = TheTerrain->GetPlane(row, col - 1);
            }
        }
        else if (KEY_IS_RIGHT)
        {
            if (col < TheLevel->GetWidthZ() - 1)
            {
                selectedPlane = TheTerrain->GetPlane(row, col + 1);
            }
        }
        else if (KEY_IS_UP)
        {
            if (row > 0)
            {
                selectedPlane = TheTerrain->GetPlane(row - 1, col);
            }
        }
        else if (KEY_IS_DOWN)
        {
            if (row < TheLevel->GetHeightX() - 1)
            {
                selectedPlane = TheTerrain->GetPlane(row + 1, col);
            }
        }
    }
}

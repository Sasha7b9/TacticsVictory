// 2021/02/17 13:13:02 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Audio/TSounds.h"
#include "Game/TParticles.h"
#include "GUI/TCursor.h"
#include "GUI/GuiGame/TWindowTarget.h"
#include "Scene/TCScene.h"
#include "Scene/Objects/Buildings/_TMilitaryPlant.h"


CScene::CScene(Context *context) : TScene(context)
{
    scene->CreateComponent<Octree>();
}


CScene::~CScene()
{
    delete TheWindowTarget;

    pathIndicator.Stop();
}


void CScene::Create()
{
    TScene::Create();

    Particles::Init();

    Sounds::Init();

    TheRenderer->SetShadowMapSize(2048);

    TheWindowTarget = new WindowTarget();
    TheUIRoot->AddChild(TheWindowTarget);
    TheWindowTarget->SetVisible(false);

    SharedPtr<MilitaryPlant> militaryPlant = MilitaryPlant::Create();
    militaryPlant->SetCoord(Coord(0, 0));

    pathIndicator.Init();

    SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(CScene, HandleMouseDown));
}


void CScene::Update(float timeStep)
{
    TScene::Update(timeStep);

    Vector3 hitPos;
    Drawable *drawable = TheCursor->GetRaycastNode(&hitPos);

    if (drawable)
    {
        String name = drawable->GetNode()->GetName();
        if (name == NODE_TERRAIN)
        {
            TheCursor->SetNormal();
        }
        else if (name == NODE_TANK)
        {
            TheCursor->SetSelected();
        }
    }
    else
    {
        TheCursor->SetNormal();
    }

    pathIndicator.Update();
}


void CScene::HandleMouseDown(StringHash, VariantMap &eventData) //-V2009
{
    int buttons = static_cast<int>(eventData[MouseButtonDown::P_BUTTONS].GetInt());

    if (buttons == MOUSEB_LEFT)
    {
        ProcessMouseLeft();
    }
    else if (buttons == MOUSEB_RIGHT)
    {
        ProcessMouseRight();
    }
}


void CScene::ProcessMouseLeft()
{
    Vector3 hitCoord;
    Drawable *object = TheCursor->GetRaycastNode(&hitCoord);

    if (!object)
    {
        return;
    }

    Node *node = object->GetNode();
    String name = node->GetName();

    if (name == NODE_TANK)
    {
        Tank *tank = node->GetComponent<Tank>();
        SetSelected(tank, !tank->IsSelected());

        Vector3 position = node->GetPosition();
        Coord coord(static_cast<uint>(-position.z_), static_cast<uint>(position.x_)); //-V2004

        pathIndicator.SetStartPosition(coord);
        pathIndicator.Enable(false);
        if (tank->IsSelected())
        {
            pathIndicator.Enable(true);
        }
    }
    else if (name == NODE_TERRAIN)
    {
        pathIndicator.Enable(true);
        Tank *tank = GetSelected();

        if (tank)
        {
            SetSelected(tank, false);
            tank->SetPath(pathIndicator.GetPath());
        }
    }
}


void CScene::ProcessMouseRight()
{
    pathIndicator.Enable(false);

    Drawable *object = TheCursor->GetRaycastNode();

    if (object && object->GetNode()->GetName() == NODE_TANK)
    {
        object->GetNode()->GetComponent<Tank>()->EnableContextMenu();
    }
}

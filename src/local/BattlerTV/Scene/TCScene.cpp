// 2021/02/17 13:13:02 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Audio/TSounds.h"
#include "Game/TParticles.h"
#include "GUI/TCursor.h"
#include "GUI/GuiGame/TWindowTarget.h"
#include "Scene/TCScene.h"


CScene::CScene(Context *context) : TScene(context)
{
    CreateComponent<Octree>();

    ThePhysicsWorld = CreateComponent<PhysicsWorld>();

    ThePhysicsWorld->SetGravity(Vector3::ZERO);
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

    pathIndicator.Init();

    SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(CScene, HandleMouseDown));
}


void CScene::HandleMouseDown(StringHash, VariantMap &eventData)
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
        Vector3 position = node->GetPosition();
        Coord coord(static_cast<uint>(-position.z_), static_cast<uint>(position.x_)); //-V2004

        pathIndicator.SetStartPosition(coord);
        pathIndicator.Enable(false);
    }
    else if (name == NODE_TERRAIN)
    {
        pathIndicator.Enable(true);
    }
}


void CScene::ProcessMouseRight()
{
    pathIndicator.Enable(false);

    Drawable *object = TheCursor->GetRaycastNode();

    if (object && object->GetNode()->GetName() == NODE_TANK)
    {
    }
}

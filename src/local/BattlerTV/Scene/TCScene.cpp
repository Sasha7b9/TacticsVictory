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
}

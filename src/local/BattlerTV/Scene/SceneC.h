// 2021/02/17 13:13:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Game/Path/PathIndicator.h"
#include "Scene/Scene_.h"


class CScene : public SceneT
{
    URHO3D_OBJECT(CScene, SceneT);

public:

    CScene(Context *context = TheContext);
    virtual ~CScene();

    virtual void Create() override;
};

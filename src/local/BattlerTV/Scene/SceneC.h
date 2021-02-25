// 2021/02/17 13:13:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Game/Path/TPathIndicator.h"
#include "Scene/TScene_.h"


class CScene : public TScene
{
    URHO3D_OBJECT(CScene, TScene);

public:

    CScene(Context *context = TheContext);
    virtual ~CScene();

    virtual void Create() override;
};
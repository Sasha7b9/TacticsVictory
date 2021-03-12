// 2021/02/17 13:13:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Game/Path/PathIndicator.h"
#include "Scene/Scene_.h"


class SceneC : public SceneT
{
public:

    SceneC(SceneC **self);
    virtual ~SceneC();

    virtual void Create() override;
};

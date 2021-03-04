// 2021/03/04 10:35:52 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Scene_.h"


class SceneS : public SceneT
{
    URHO3D_OBJECT(SceneS, SceneT);

public:

    SceneS(Context *context = TheContext) : SceneT(context) {}
    virtual ~SceneS() {}
};

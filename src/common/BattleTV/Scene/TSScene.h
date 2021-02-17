// 2021/02/17 16:49:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/_TScene.h"


class SScene : public TScene
{
    URHO3D_OBJECT(SScene, TScene);

public:

    SScene(Context *context = TheContext) : TScene(context) {}

    virtual SharedPtr<Tank> CreateTank() override;

    virtual void Existor() override {}

    static void RegisterObject(Context *context = TheContext);
};

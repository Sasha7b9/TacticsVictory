// 2021/02/17 13:13:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/_TScene.h"


class CScene : public TScene
{
    URHO3D_OBJECT(CScene, TScene);

public:

    CScene(Context *context = TheContext) : TScene(context) {};
    virtual ~CScene();

    virtual void Create() override;

    virtual void Update(float timeStep) override;

private:
    PathIndicator pathIndicator;

    void HandleMouseDown(StringHash, VariantMap &);
    void ProcessMouseLeft();
    void ProcessMouseRight();
};

/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once

#ifdef CLIENT
#include "Game/Path/TPathIndicator.h"
#endif

class Tank;

class TScene : public Object
{
    URHO3D_OBJECT(TScene, Object);

public:

    TScene(Context *context = TheContext);
    virtual ~TScene();

    static void RegisterObject(Context *context = TheContext);

    virtual void Update(float timeStep);
    virtual void Create();

    void SetSelected(Tank *node, bool selected);
    Tank* GetSelected();

    Vector<Vector<float>> level;

    Scene *scene = nullptr;

private:

    void RegisterObjects();
};

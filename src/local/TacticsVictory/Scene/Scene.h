/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Game/Path/PathIndicator.h"


class SceneRTS : public Object
{
    URHO3D_OBJECT(SceneRTS, Object);

public:

    SceneRTS(Context *context = TheContext);
    ~SceneRTS();

    static void RegisterObject(Context *context = TheContext);

    void Update(float timeStep);
    void Create();

    void SetSelected(Tank *node, bool selected);
    Tank* GetSelected();

    Vector<Vector<float>> level;

    Scene *scene = nullptr;

private:
    PathIndicator pathIndicator;

    void RegisterObjects();
    void HandleMouseDown(StringHash, VariantMap&);
    void ProcessMouseLeft();
    void ProcessMouseRight();
};

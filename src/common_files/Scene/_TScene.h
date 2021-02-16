/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once

#ifdef CLIENT
#include "Game/Path/PathIndicator.h"
#endif

class Tank;

class TScene : public Object
{
    URHO3D_OBJECT(TScene, Object);

public:

    enum Mode
    {
        Mode_Server,
        Mode_Client
    };

    TScene(Context *context = TheContext, Mode mode = Mode_Server);
    ~TScene();

    static void RegisterObject(Context *context = TheContext);

    void Update(float timeStep);
    void Create();

    void SetSelected(Tank *node, bool selected);
    Tank* GetSelected();

    Vector<Vector<float>> level;

    Scene *scene = nullptr;

private:

    Mode mode;

    void RegisterObjects();

#ifdef CLIENT

    void HandleMouseDown(StringHash, VariantMap &);
    void ProcessMouseLeft();
    void ProcessMouseRight();

private:
    PathIndicator pathIndicator;

#endif
};

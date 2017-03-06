#pragma once
#include "Game/Objects/Units/Tank/Tank.h"
#include "Game/Path/PathIndicator.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SceneRTS : public Object
{
    URHO3D_OBJECT(SceneRTS, Object);

public:

    enum Mode
    {
        Mode_Server,
        Mode_Client
    };

    SceneRTS(Context *context = gContext, Mode mode = Mode_Server);
    ~SceneRTS();

    static void RegisterObject(Context *context = gContext);

    void Update(float timeStep);
    void Create();

    void SetSelected(Tank *node, bool selected);
    Tank* GetSelected();

    Vector<Vector<float>> level;

private:
    PathIndicator pathIndicator;
    Mode mode;

    void RegisterObjects();
    void HandleMouseDown(StringHash, VariantMap&);
    void ProcessMouseLeft();
    void ProcessMouseRight();

    DEFAULT_MEMBERS(SceneRTS);
};

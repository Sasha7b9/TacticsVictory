#pragma once
#include "GUI/Controls/WindowRTS.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WindowTarget : public WindowRTS
{
    URHO3D_OBJECT(WindowTarget, WindowRTS);

public:
    WindowTarget(Context *context = gContext);
    void AddTank(Tank *tank);

public:
    void HandleSetTexture(StringHash, VariantMap&);
};

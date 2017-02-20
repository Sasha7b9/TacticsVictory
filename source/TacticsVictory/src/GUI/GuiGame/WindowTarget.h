#pragma once


#include "GUI/Elements/Window.h"


class WindowTarget : public lWindow
{
    URHO3D_OBJECT(WindowTarget, lWindow);

public:
    WindowTarget(Context *context = gContext);

    void AddTank(Tank *tank);

public:
    void HandleSetTexture(StringHash, VariantMap&);
};
// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/WindowRTS.h"



class WindowTarget : public WindowRTS
{
    URHO3D_OBJECT(WindowTarget, WindowRTS);

public:
    WindowTarget(Context *context = TheContext);
    void AddTank(Tank *tank);

public:
    void HandleSetTexture(StringHash, VariantMap&);

    DEFAULT_MEMBERS(WindowTarget);
};

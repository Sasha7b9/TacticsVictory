// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/_TWindow.h"


class Tank;


class WindowTarget : public WindowTV
{
    URHO3D_OBJECT(WindowTarget, WindowTV);

public:
    WindowTarget(Context *context = TheContext);
    void AddTank(Tank *tank);

public:
    void HandleSetTexture(StringHash, VariantMap&);
};

// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Control_.h"


class Tank;


class WindowTarget : public Control
{
    URHO3D_OBJECT(WindowTarget, Control);

public:

    WindowTarget();

    void AddTank(Tank *tank);

private:

    static const int WIDTH = 500;
    static const int HEIGHT = 300;
};

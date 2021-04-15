// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/GUI_.h"
#include "GUI/Controls/Control_.h"


class GUI : public GUIT
{
    URHO3D_OBJECT(GUI, GUIT);

public:
    GUI(GUI **self);
    ~GUI();

    void SetVisibleWindow(Control *window, bool visible);
    void SetUnvisibleAllWindows();

private:
    void Create();
};

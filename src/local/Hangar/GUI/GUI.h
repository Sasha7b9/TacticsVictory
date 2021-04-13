// 2021/04/12 22:58:28 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/GUI_.h"


class GUI : public GUIT
{
    URHO3D_OBJECT(GUI, GUIT);

public:

    GUI(GUI **self);

private:

    void Create();
    void RegistrationObjects();
};

// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Window_.h"


/*
    ������ ������ - �� ��� ����������� ������
*/
class PanelBottom : public WindowT
{
    URHO3D_OBJECT(PanelBottom, WindowT);

public:
    PanelBottom(Context *context = TheContext);
    static void RegisterObject();
};

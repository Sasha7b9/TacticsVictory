// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/_WindowRTS.h"


/*
    ������ ������ - �� ��� ����������� ������
*/
class PanelBottom : public WindowRTS
{
    URHO3D_OBJECT(PanelBottom, WindowRTS);

public:
    PanelBottom(Context *context = TheContext);

    static void RegisterObject(Context *context = TheContext);
};

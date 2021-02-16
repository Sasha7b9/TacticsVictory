// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/_WindowRTS.h"


/*
    Нижняя панель - на ней расположены кнопки
*/
class PanelBottom : public WindowTV
{
    URHO3D_OBJECT(PanelBottom, WindowTV);

public:
    PanelBottom(Context *context = TheContext);

    static void RegisterObject(Context *context = TheContext);
};

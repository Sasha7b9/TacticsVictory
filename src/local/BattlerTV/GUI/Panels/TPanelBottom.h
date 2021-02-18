// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/_TWindow.h"


/*
    Нижняя панель - на ней расположены кнопки
*/
class PanelBottom : public TWindow
{
    URHO3D_OBJECT(PanelBottom, TWindow);

public:
    PanelBottom(Context *context = TheContext);

    static void RegisterObject(Context *context = TheContext);
};

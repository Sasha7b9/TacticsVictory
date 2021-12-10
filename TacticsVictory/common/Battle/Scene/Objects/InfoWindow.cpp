// 2021/12/3 1:23:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/InfoWindow.h"


using namespace Pi;


InfoWindow::InfoWindow() : DrawingWidget({50, 20})
{
    SetColorBackground({0.0f, 0.0f, 0.0f, 0.5f});
    SetColorBrush({1.0f, 1.0f, 1.0f});

    Clear();

    DrawRectangle(0, 0, GetWidgetSize().x - 1, GetWidgetSize().y - 1);

    EndScene();
}

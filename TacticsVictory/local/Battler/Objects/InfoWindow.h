// 2021/12/3 1:24:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Widgets/DrawingWidget.h"


namespace Pi
{
    // Здесь отображется информация о юните при наведении на него курсора и выделении
    class InfoWindow : public DrawingWidget
    {
    public:
        InfoWindow();
        virtual ~InfoWindow() {};
    };
}

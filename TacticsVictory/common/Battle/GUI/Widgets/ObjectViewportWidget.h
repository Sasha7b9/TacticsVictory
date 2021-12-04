// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "DrawingWidget.h"


namespace Pi
{

    class ObjectViewportWidget : public DrawingWidget
    {
    
    public:
    
        ObjectViewportWidget(const Vector2D& size, float focalLength);
    
    private:
      
        WorldViewportWidget *viewport = nullptr;
    };

}

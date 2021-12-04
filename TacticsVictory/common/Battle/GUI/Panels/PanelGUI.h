#pragma once
#include "GUI/Widgets/DrawingWidget.h"


namespace Pi
{

    class Movinator;
    class TButton;
    
    
    class PanelGUI : public DrawingWidget {
    
    public:
        PanelGUI(const Vector2D &size);
        virtual ~PanelGUI();
    
        void SetMovementMutator(Point2D posShow, Point2D posHide, Vector2D speed);
        void Toggle();
        void Preprocess() override;
        void Clear();
    
    protected:
        virtual void Update() override {};
    };

}

#pragma once
#include "PanelGUI.h"
#include "GUI/Widgets/Button.h"
#include "Input/Mouse.h"


namespace Pi
{

    class PanelMapMutator;
    
    
    enum
    {
        kMutatorPanelMap = 'map_'
    };
    
    
    class PanelMap : public PanelGUI, public Singleton<PanelMap> {
    
    public:
        PanelMap();
        virtual ~PanelMap();
    
        void Preprocess() override;
        void HandleHideShow(Widget *button, const WidgetEventData *data);
        void HandleObserver(MouseObservable *, uint);
    
    private:
    
        PanelMapMutator *mutator = nullptr;
        Observer<PanelMap, MouseObservable> *observer = nullptr;
    };
    
    
    extern PanelMap *ThePanelMap;
    
    
    class PanelMapMutator : public Mutator
    {
        
        friend class MutatorReg < PanelMapMutator > ;
    
    public:
        PanelMapMutator(PanelMap *panel);
    
        void Move() override;
        void Reset() override;
    
        static Point2D CoordWorldToMap(const Point3D &coord);
        static Point3D CoordMapToWorld(const Point2D &coord);
    
    private:
    
        PanelMap *panel = nullptr;
        static float scale;
        static Point2D leftTop;
    
        Mutator *Replicate() const override;
    };

}

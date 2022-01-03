// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/World/CameraRTS.h"


namespace Pi
{

    namespace PiTypeAction
    {
        // NavigationAction
        const S Forward   = 'frwd';     // W
        const S Backward  = 'bkwd';     // S
        const S Left      = 'left';     // A
        const S Right     = 'rght';     // D
    
        const S RotLeft   = 'rotl';     // Num 4
        const S RotRight  = 'rotr';     // Num 6
        const S RotTop    = 'rott';     // Num 9
        const S RotDown   = 'rotd';     // Num 3
        const S ZoomIn    = 'zmin';     // Num 2
        const S ZoomOut   = 'zmot';     // Num 8
        const S Center    = 'cntr';     // Num 5    направить камеру на центр сцены
    
        // KeyboardAction
        const S F1        = 'kF1';      // "F1"
        const S F2        = 'kF2';      // "F2"
        const S Esc       = 'esc';      // "Esc"
    
        // MouseAction
        const S MouseLeft   = 'lbtn';   // "Кнопка 0"
        const S MouseRight  = 'mbtn';   // "Кнопка 1"
        const S MouseMiddle = 'rbtn';   // "Кнопка 2"
        const S MouseWheel  = 'weel';   // "Колесико"
    }
    
    
    class NavigationAction : public Action 
    {
    public:
    
        NavigationAction(PiTypeAction::S type, CameraRTS::E flag) : Action(type) { movementFlag = flag; }
        virtual ~NavigationAction()    { }
        void Begin() { CameraRTS::self->AddNavFlag(movementFlag);    }
        void End()   { CameraRTS::self->RemoveNavFlag(movementFlag); }
    
    private:
        CameraRTS::E movementFlag;
    };
    
    
    class KeyboardAction : public Action
    {
    public:
        KeyboardAction(PiTypeAction::S type) : Action(type)    {    }
        virtual ~KeyboardAction()    {    }
        void Begin();
        void End(){};
    };
    
    
    class MouseButtonAction : public Action 
    {
    public:
        MouseButtonAction(ulong type) : Action(type) {};
        virtual ~MouseButtonAction() { }
        void Begin();
        void End();
        void Update(float value);
    
    };
    
    
    class Input 
    {
    public:
        static void Init();
    };

}

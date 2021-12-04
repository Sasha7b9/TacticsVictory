// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "DrawingWidget.h"
#include "Input/Mouse.h"


namespace Pi
{

    class Console;
    
    enum 
    {
        kLineEditEventKeyEnter
    };
    
    class LineEditEventData 
    {
    public:
        EventT eventType;
        String<>   text;
    
        LineEditEventData() = delete;
    
        LineEditEventData(EventT type, char *eText)  : eventType(type)
        {
            text = String<>(eText);
        }
    };
    
    class LineEditObservable : public Observable < LineEditObservable, LineEditEventData> 
    {
    public:
        LineEditObservable() {};
        virtual ~LineEditObservable() {};
    };
    
    class LineEdit : public DrawingWidget 
    {
    public:
        LineEdit(const Vector2D &size = Vector2D(10.0f, 10.0f));
        
       void HandleMouseEvent(const PanelMouseEventData *eventData) override;
       bool HandleKeyboardEvent(const KeyboardEventData *eventData) override;
    
       void AddObserver(Observer<Console, LineEditObservable> *observer);
    
    private:
        LineEditObservable observable;
        int posCursor = 0;
        Array<char> text;
        TextWidget textWidget;
    
        void Redraw();
        char *TextFromArray();
    };

}

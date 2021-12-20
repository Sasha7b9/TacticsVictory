// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "DrawingWidget.h"
#include "GUI/Panels/PanelMap.h"
#include "Input/Mouse.h"


namespace Pi
{

    class ButtonSkin;
    
    
    class TButton : public Widget
    {
    public:
    
        enum class Type
        {
            Normal,
            NameTab
        };
    
        TButton(Type type, const Vector2D &position, pchar text);
        ~TButton();
    
        virtual void Move() override { };
        virtual void Update() override { };
        void SetSelected(bool selected);        // Only for TypeNameTab
    
        void HandleObserver(MouseObservable *, uint);
    
    protected:
        Type buttonType = Type::Normal;
    
    private:
        Array<ButtonSkin *> skins;
        bool selected = false;
        Observer<TButton, MouseObservable> *observer = nullptr;
        WidgetEventData eventData;
    
        void SetState(uint buttonState);
    };
    
    
    class ButtonSkin : public DrawingWidget
    {
    public:
    
        enum class State
        {
            Normal,
            UnderMouse,
            Pressed
        };
    
        ButtonSkin(TButton::Type type, const char* text, State state);
    
    private:
        void DrawSkin(TButton::Type type, const ColorRGBA& colorBackground, const ColorRGBA& colorBorder);
    };

}

// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "DrawingWidget.h"
#include "LineEdit.h"


namespace Pi
{
    class Console : public DrawingWidget, public Singleton<Console>
    {

    public:
        Console(const Vector2D &size);
        virtual ~Console();

        static Console *self;

        void Toggle();
        bool IsOpen()
        {
            return isOpen;
        };
        static bool OnKeyboardEvent(const KeyboardEventData *eventData, void *data);

    private:
        static LineEdit *lineEdit;
        bool isOpen = true;
        KeyboardEventHandler *keyboardEventHandler = nullptr;

        void CaptureKeyboard();
        void ReleaseKeyboard();
    };
}

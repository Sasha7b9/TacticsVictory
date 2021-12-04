// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "LineEdit.h"


using namespace Pi;


LineEdit::LineEdit(const Vector2D &size) : DrawingWidget(size) 
{
    SetColorBrush(K::white);
    textWidget.SetWidgetColor(K::white);
    textWidget.SetFont("fonts/Techno28_14");
    textWidget.SetWidgetPosition({ 2.0f, 2.0f, 0.0f });
    AppendNewSubnode(&textWidget);
    Redraw();
    EndScene();
}

void LineEdit::HandleMouseEvent(const PanelMouseEventData * /*eventData*/) 
{
}

bool LineEdit::HandleKeyboardEvent(const KeyboardEventData * eventData) 
{
    EventKeyboard::S type = eventData->eventType;
    KeyCode::E code = eventData->keyCode;

    if (type == EventKeyboard::KeyDown)
    {
        if (code == KeyCode::Enter)
        {
            text.AddElement(0);
            observable.PostEvent(LineEditEventData(kLineEditEventKeyEnter, text.begin()));
            text.RemoveElement(text.GetElementCount() - 1);
        } 
        else if (code == KeyCode::Backspace) 
        {
            if (posCursor > 0)
            {
                text.RemoveElement(text.GetElementCount() - 1);
                posCursor--;
                Redraw();
            }
        }
        else if (code == KeyCode::Delete) 
        {
            text.RemoveElement(posCursor);
            Redraw();
        }
        else if (code == KeyCode::LeftArrow)
        {
            if (posCursor > 0)
            {
                posCursor--;
                Redraw();
            }
        }
        else if (code == KeyCode::RightArrow)
        {
            if (posCursor < text.GetElementCount())
            {
                posCursor++;
                Redraw();
            }
        }
#define MIN_CODE_SYMBOL 0x20
        else if ((int)code >= MIN_CODE_SYMBOL)
        {
            text.InsertElement(posCursor, toupper((int)code));
            posCursor++;
            Redraw();
        }
    }
    return false;
}

void LineEdit::AddObserver(Observer<Console, LineEditObservable> *observer)
{
    observable.AddObserver(observer);
}

void LineEdit::Redraw()
{
    DrawRectangle(0.0f, 0.0f, GetWidgetSize().x - 1, GetWidgetSize().y - 1);
    textWidget.SetWidgetSize(GetWidgetSize());
    textWidget.SetText(TextFromArray());
    Invalidate();
}

char* LineEdit::TextFromArray()
{
    int length = text.GetElementCount() + 1;
    static const int LENGTH_BUFFER = 1024;
    static char buffer[LENGTH_BUFFER];
    memcpy(buffer, text.begin(), (size_t)(length - 1));
    buffer[length - 1] = '\0';
    return buffer;
}

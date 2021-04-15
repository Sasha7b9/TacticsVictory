// 2021/04/12 23:12:09 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Windows/Chat.h"


Chat::Chat() : WindowT()
{
    SetSize(500, 500);
    SetResizable(true);

    lineEdit = TheUIRoot->CreateChild<LineEdit>();
    
    lineEdit->SetStyle("LineEdit");
    AddChild(lineEdit);

    text = TheUIRoot->CreateChild<Text>();

    text->SetWordwrap(true);
    AddChild(text);

    SubscribeToEvent(lineEdit, E_TEXTFINISHED, URHO3D_HANDLER(Chat, HandlerFinishedText));
    SubscribeToEvent(lineEdit, E_UNHANDLEDKEY, URHO3D_HANDLER(Chat, HandlerUnhandledKey));
    SubscribeToEvent(text, E_CLICK, URHO3D_HANDLER(Chat, HandlerClick));
    SubscribeToEvent(this, E_CLICK, URHO3D_HANDLER(Chat, HandlerClick));

    VariantMap map;
    HandlerResize("", map);
}


void Chat::HandlerFinishedText(StringHash, VariantMap &)
{

}


void Chat::HandlerUnhandledKey(StringHash, VariantMap &)
{

}


void Chat::HandlerClick(StringHash, VariantMap &)
{

}


void Chat::CallbackOnResize()
{
    if (!lineEdit)
    {
        return;
    }

    lineEdit->SetSize(GetWidth() - 20, 15);
    lineEdit->SetPosition(2, GetHeight() - 15);

    text->SetFixedSize(GetWidth(), GetHeight() - 20);
    text->SetPosition(2, 0);

    // Теперь ограничим количество строк
    static const uint MAX_STRINGS = 100;

    while (text->GetNumRows() > MAX_STRINGS)
    {
        uint pos = text->GetText().Find("\n");
        text->SetText(text->GetText().Substring(pos + 2));
    }

    int height = GetHeight();
    int heightText = text->GetHeight() + 15;

    if (heightText > height)
    {
        IntVector2 pos = text->GetPosition();
        pos.y_ = -(heightText - height);
        text->SetPosition(pos);
    }
}

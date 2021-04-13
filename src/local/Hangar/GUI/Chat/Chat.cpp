// 2021/04/12 23:12:09 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Chat/Chat.h"


Chat::Chat() : WindowT(TheContext)
{
    SetSize(500, 500);
    SetResizable(false);

    line_edit = TheUIRoot->CreateChild<LineEdit>();
    
    line_edit->SetStyle("LineEdit");
    AddChild(line_edit);

    text = TheUIRoot->CreateChild<Text>();

    text->SetWordwrap(true);
    AddChild(text);

    SubscribeToEvent(line_edit, E_TEXTFINISHED, URHO3D_HANDLER(Chat, HandlerFinishedText));
    SubscribeToEvent(line_edit, E_UNHANDLEDKEY, URHO3D_HANDLER(Chat, HandlerUnhandledKey));
    SubscribeToEvent(text, E_CLICK, URHO3D_HANDLER(Chat, HandlerClick));
    SubscribeToEvent(this, E_CLICK, URHO3D_HANDLER(Chat, HandlerClick));

    VariantMap map;

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

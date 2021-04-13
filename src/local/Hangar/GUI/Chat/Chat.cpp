// 2021/04/12 23:12:09 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Chat/Chat.h"


Chat::Chat() : WindowT(TheContext)
{
    SetSize(500, 500);
    SetResizable(false);

    line_edit = TheUIRoot->CreateChild<LineEdit>();
    
    bool result = line_edit->SetStyle("LineEdit");

    if (!result)
    {
        LOGERROR("Can not set style LineEdit");
    }

    AddChild(line_edit);

    text = TheUIRoot->CreateChild<Text>();
    result = text->SetStyle("MenuPage");

    if (!result)
    {
        LOGERROR("Can not set style MenuPage");
    }

    text->SetWordwrap(true);
    AddChild(text);

    SubscribeToEvent(line_edit, E_TEXTFINISHED, URHO3D_HANDLER(Chat, HandleFinishedText));
    SubscribeToEvent(line_edit, E_UNHANDLEDKEY, URHO3D_HANDLER(Chat, HandleUnhandledKey));
    SubscribeToEvent(text, E_CLICK, URHO3D_HANDLER(Chat, HandleClick));
    SubscribeToEvent(this, E_CLICK, URHO3D_HANDLER(Chat, HandleClick));
}


void Chat::HandleFinishedText(StringHash, VariantMap &)
{

}


void Chat::HandleUnhandledKey(StringHash, VariantMap &)
{

}


void Chat::HandleClick(StringHash, VariantMap &)
{

}

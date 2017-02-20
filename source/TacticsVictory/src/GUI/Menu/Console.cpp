#include <stdafx.h>


#include "Console.h"
#include "GUI/Menu/ConsoleParser.h"


lConsole::lConsole(Context *context) :
    lWindow(context)
{
    SetVisible(false);

    SetSize(1500, 300);
    SetResizable(true);

    lineEdit = gUIRoot->CreateChild<Urho3D::LineEdit>();
    lineEdit->SetStyle("LineEdit");
    lineEdit->SetSize(GetWidth(), 15);
    lineEdit->SetPosition(0, GetHeight() - 15);

    AddChild(lineEdit);

    scrollBar = gUIRoot->CreateChild<ScrollBar>();
    scrollBar->SetFixedSize(10, GetHeight() - 15);
    scrollBar->SetPosition(GetWidth() - 10, 0);
    scrollBar->SetStyleAuto();
    scrollBar->SetOrientation(Urho3D::O_VERTICAL);
    scrollBar->SetRange(0.0f);
    AddChild(scrollBar);

    text = gUIRoot->CreateChild<Urho3D::Text>();
    text->SetStyle("WindowMenu");
    text->SetFixedSize(GetWidth() - 10, GetHeight() - 15);
    text->SetPosition(0, 0);
    AddChild(text);

    SubscribeToEvent(lineEdit, Urho3D::E_TEXTFINISHED, URHO3D_HANDLER(lConsole, HandleFinishedText));
}

void lConsole::Toggle()
{
   SetVisible(!IsVisible());
   if(IsVisible())
   {
       gUI->SetFocusElement(lineEdit);
   }
}

void lConsole::HandleFinishedText(StringHash, VariantMap&)
{
    String command = lineEdit->GetText();
    if(command.Empty())
    {
        return;
    }
    ConsoleParser::Execute(command);
    text->SetText(text->GetText() + command + "\n");
    lineEdit->SetText("");
}
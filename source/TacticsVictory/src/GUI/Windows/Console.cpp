#include <stdafx.h>
#include "Console.h"
#include "GUI/Windows/ConsoleParser.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ConsoleRTS::ConsoleRTS(Context *context) :
    WindowRTS(context)
{
    SetVisible(false);

    SetSize(1500, 300);
    SetResizable(true);

    lineEdit = gUIRoot->CreateChild<LineEdit>();
    lineEdit->SetStyle("LineEdit");
    lineEdit->SetSize(GetWidth(), 15);
    lineEdit->SetPosition(0, GetHeight() - 15);

    AddChild(lineEdit);

    scrollBar = gUIRoot->CreateChild<ScrollBar>();
    scrollBar->SetFixedSize(10, GetHeight() - 15);
    scrollBar->SetPosition(GetWidth() - 10, 0);
    scrollBar->SetStyleAuto();
    scrollBar->SetOrientation(O_VERTICAL);
    scrollBar->SetRange(0.0f);
    AddChild(scrollBar);

    text = gUIRoot->CreateChild<Text>();
    text->SetStyle("WindowMenu");
    text->SetFixedSize(GetWidth() - 10, GetHeight() - 15);
    text->SetPosition(0, 0);
    AddChild(text);

    SubscribeToEvent(lineEdit, E_TEXTFINISHED, URHO3D_HANDLER(ConsoleRTS, HandleFinishedText));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ConsoleRTS::Toggle()
{
   SetVisible(!IsVisible());
   if(IsVisible())
   {
       gUI->SetFocusElement(lineEdit);
   }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ConsoleRTS::HandleFinishedText(StringHash, VariantMap&)
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

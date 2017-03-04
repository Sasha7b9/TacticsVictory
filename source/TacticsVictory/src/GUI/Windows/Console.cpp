#include <stdafx.h>
#include "Console.h"
#include "GUI/Windows/WindowVariables.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HashMap<String, ConsoleParser::ParserStruct> ConsoleParser::commands;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void FuncExit(Vector<String> &)
{
    gEngine->Exit();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void FuncVars(Vector<String> &words)
{
    uint size = words.Size();

    String word0 = size > 0 ? words[0] : "";
    String word1 = size > 1 ? words[1] : "";

    if(size == 1)
    {
        gWindowVars->SetVisible(!gWindowVars->IsVisible());
    }
    else if(size == 2)
    {
        if(word1 == "open")
        {
            gWindowVars->SetVisible(true);
        }
        else if(word1 == "close")
        {
            gWindowVars->SetVisible(false);
        }
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsoleParser::Init()
{
    ConsoleParser::commands.Insert({"exit", {FuncExit}});
    ConsoleParser::commands.Insert({"vars", {FuncVars}});
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ConsoleParser::Execute(const String &string)
{
    Vector<String> words = string.Split(' ');

    pFuncVvS func = commands[words[0]].func;

    func(words);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ConsoleRTS::ConsoleRTS(Context *context) :
    WindowRTS(context)
{
    ConsoleParser::Init();

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
bool ConsoleRTS::IsActive()
{
    return lineEdit->HasFocus();
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

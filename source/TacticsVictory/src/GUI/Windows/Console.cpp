#include <stdafx.h>
#include "Console.h"
#include "GUI/Windows/WindowVariables.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HashMap<String, ConsoleParser::ParserStruct> ConsoleParser::commands;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool FuncHelp(Vector<String> &)
{
    gConsole->Write(L"         Справка по командам");

    for(HashMap<String, ConsoleParser::ParserStruct>::KeyValue key : ConsoleParser::commands)
    {
        if(key.first_ != "?")
        {
            gConsole->Write(key.first_ + " " + key.second_.help);
        }
    }
    return true;
}

static bool FuncExit(Vector<String> &)
{
    gEngine->Exit();
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool FuncVars(Vector<String> &words)
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
        else
        {
            return false;
        }
    }

    return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsoleParser::Init()
{
    ParserStruct structHelp = {FuncHelp};
    structHelp.help = L"Вывод справки";
    ConsoleParser::commands.Insert({"?", structHelp});

    ParserStruct structVars = {FuncVars};
    structVars.help = L"Переключить окно переменных. open - открыть, close - закрыть";
    ConsoleParser::commands.Insert({"vars", structVars});

    ParserStruct structExit = {FuncExit};
    structExit.help = L"Выход";
    ConsoleParser::commands.Insert({"exit", structExit});

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::Execute(const String &string)
{
    Vector<String> words = string.ToLower().Split(' ');

    if(commands.Contains(words[0]))
    {
        pFuncBvS func = commands[words[0]].func;

        if(func)
        {
            return func(words);
        }
    }

    return false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ConsoleRTS::ConsoleRTS(Context *context) :
    WindowRTS(context)
{
    ConsoleParser::Init();

    SetVisible(false);
    SetResizable(true);

    SetSize(1500, 300);
    SetResizable(true);

    lineEdit = gUIRoot->CreateChild<LineEdit>();
    lineEdit->SetStyle("LineEdit");
    lineEdit->SetSize(GetWidth()- 2, 15);
    lineEdit->SetPosition(2, GetHeight() - 15);

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
    text->SetPosition(2, 0);
    AddChild(text);

    SubscribeToEvent(lineEdit, E_TEXTFINISHED, URHO3D_HANDLER(ConsoleRTS, HandleFinishedText));
    SubscribeToEvent(lineEdit, E_UNHANDLEDKEY, URHO3D_HANDLER(ConsoleRTS, HandleUnhandledKey));
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
    history.AddString(command);

    Write("> " + command);

    if(!ConsoleParser::Execute(command))
    {
        Write(L"Неизвестная команда. Для получения справки наберите \"?\"");

    }

    lineEdit->SetText("");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ConsoleRTS::HandleUnhandledKey(StringHash, VariantMap& eventData)
{
    using namespace UnhandledKey;
    int key = eventData[P_KEY].GetInt();

    if(key == KEY_UP)
    {
        lineEdit->SetText(history.GetPrev());
    }
    else if(key == KEY_DOWN)
    {
        lineEdit->SetText(history.GetNext());
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ConsoleRTS::Write(const String &message)
{
    text->SetText(text->GetText() + message + "\n");

    int height = GetHeight();
    int heightText = text->GetHeight() + 15;

    if(heightText > height)
    {
        IntVector2 pos = text->GetPosition();
        pos.y_ = -(heightText - height);
        text->SetPosition(pos);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void History::AddString(String &string)
{
    if(strings.Contains(string))
    {
        strings.Remove(string);
    }
    strings.Push(string);
    position = (int)strings.Size();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
String History::GetPrev()
{
    if(strings.Size() == 0)
    {
        return String::EMPTY;
    }

    position--;
    if(position < 0)
    {
        position = (int)strings.Size() - 1;
    }

    return strings[(uint)position];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
String History::GetNext()
{
    if(strings.Size() == 0)
    {
        return String::EMPTY;
    }

    position++;
    if(position > (int)strings.Size() - 1)
    {
        position = 0;
    }

    return strings[(uint)position];
}

#include <stdafx.h>
#include "Console.h"
#include "GlobalFunctions.h"
#include "GUI/Windows/WindowVariables.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HashMap<String, ConsoleParser::ParserStruct> ConsoleParser::commands;

#define TAB "    "


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool FuncHelp(Vector<String> &)
{
    gConsole->Write(String(TAB) + L"Справка по командам");

    // Находим максимальную длину слова
    uint len = 0;
    for(HashMap<String, ConsoleParser::ParserStruct>::KeyValue key : ConsoleParser::commands)
    {
        if(key.first_.Length() > len)
        {
            len = key.first_.Length();
        }
    }

    for(HashMap<String, ConsoleParser::ParserStruct>::KeyValue key : ConsoleParser::commands)
    {
        if(key.first_ != "?")
        {
            String message;
            message += key.first_;

            for(uint i = 0; i < len - key.first_.Length() + 1; i++)
            {
                message += " ";
            }

            gConsole->Write(message + key.second_.help);
        }
    }

    gConsole->Write(String(TAB) + L"Для получения подробной информации наберите \"vars ?\"");

    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void ShowFullInfo(Vector<String> &strings)
{
    ConsoleParser::ParserStruct parserStruct = ConsoleParser::commands[strings[0]];

    gConsole->Write(strings[0] + " " + parserStruct.fullHelp[0]);
    gConsole->Write(TAB + parserStruct.help);

    String* help = &parserStruct.fullHelp[1];
    while(!help->Empty())
    {
        gConsole->Write(TAB + *help);
        help++;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool FuncClear(Vector<String> &)
{
    gConsole->Clear();
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool FuncClose(Vector<String> &)
{
    gConsole->Toggle();
    return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsoleParser::Init()
{
    ParserStruct structs[100] =
    {
        {"?",    FuncHelp, L"Вывод справки"},
        {"clear", FuncClear, L"Очистить консоль"},
        {"close", FuncClose, L"Закрыть консоль"},
        {"exit", FuncExit, L"Выход"},
        {"vars", FuncVars, L"Управление окном переменных",
                            {"[open|close]", L"open - показать", L"close - скрыть"}
        },
    };

    ParserStruct *parserStruct = structs;

    while(parserStruct->func)
    {
        ConsoleParser::commands.Insert({parserStruct->command, *parserStruct});
        parserStruct++;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::Execute(const String &string)
{
    Vector<String> words = string.ToLower().Split(' ');

    uint numWords = words.Size();

    if(commands.Contains(words[0]))
    {
        if(numWords > 1 && words[1] == "?")
        {
            ShowFullInfo(words);
            return true;
        }

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

    String message;

#ifdef _WINDOWS

    SYSTEMTIME st;
    GetLocalTime(&st);
    message = IntToString(st.wHour, 2) + ":" + IntToString(st.wMinute, 2) + ":" + IntToString(st.wSecond, 2) + ":" + IntToString(st.wMilliseconds, 3);

#endif

    Write(message + " > " + command);

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

    if(KEY_IS_UP)
    {
        lineEdit->SetText(history.GetPrev());
    }
    else if(KEY_IS_DOWN)
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
void ConsoleRTS::Clear()
{
    text->SetText("");
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
        position = 0;
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
        position = (int)strings.Size() - 1;
    }

    return strings[(uint)position];
}

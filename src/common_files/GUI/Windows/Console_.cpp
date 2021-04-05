// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Windows/Console_.h"


#define TAB "    "


ConsoleParser::ConsoleParser() : Object(TheContext)
{

}


void ConsoleParser::Execute(const String &string)
{
    const ParserStruct structs[100] =
    {
        {"clear",   None,   &ConsoleParser::FuncClear,  "очистить консоль"},
        {"client",  None,   &ConsoleParser::FuncClient, "функции работы с клиентом"},
        {"close",   None,   &ConsoleParser::FuncClose,  "закрыть консоль"},
        {"exit",    None,   &ConsoleParser::FuncExit,   "выход"},
        {"server",  None,   &ConsoleParser::FuncServer, "функции работы с сервером"},
        {"vars",    None,   &ConsoleParser::FuncVars,   "окно переменных"},
        {"unit",    None,   &ConsoleParser::FuncUnit,   "функции упрвления юнитами"}
    };

    Vector<String> words = string.ToLower().Split(' ');

    if(!ShowBriefHelp(structs, words))
    {
        if(!ShowFullHelp(structs, words))
        {
            if(!ExecuteCommand(structs, words))
            {
                TheConsole->Write("Неизвестная команда. Для просмотра списка доступных команд наберите \"?\"");
            }
        }
    }
}


bool ConsoleParser::ShowBriefHelp(const ParserStruct *structs, const Vector<String> &words)
{
    if(words[0] == "?")
    {
        const ParserStruct *str = structs;

        uint length = 0;
        while(str->command)
        {
            if((uint)strlen(str->command) > length)
            {
                length = (uint)strlen(str->command);
            }
            str++;
        }

        str = structs;

        while(str->command)
        {
            String message = str->command;

            while(message.Length() < length + 3)
            {
                message.Append(' ');
            }

            TheConsole->Write(message + str->help);
            str++;
        }

        return true;
    }
    return false;
}


bool ConsoleParser::ShowFullHelp(const ParserStruct *structs, Vector<String> &words)
{
    const ParserStruct *str = structs;

    if(words.Size() > 1 && words[1] == "?")
    {
        while(str->command)
        {
            if(BeginFrom(words[0], str->command))
            {
                TheConsole->Write(String(str->command) + "  " + str->help);

                (this->*str->func)(words, true);

                return true;
            }
            str++;
        }
    }

    return false;
}


bool ConsoleParser::ExecuteCommand(const ParserStruct *structs, Vector<String> &words)
{
    const ParserStruct *str = structs;

    while(str->command)
    {
        if(BeginFrom(words[0], str->command))
        {
            pFuncMember func = str->func;

            String forMSG = words[0];

            words.Erase(0, 1);
            if(!(this->*func)(words, false))
            {
                TheConsole->Write(ToString("Invalid command syntax. For more information, type \"%s -?\"", forMSG.CString())); //-V111
            }

            return true;
        }

        str++;
    }

    return false;
}


bool ConsoleParser::ExtractInt(const String &str, int *value)
{
    Vector<String> words = str.Split(':');

    if(words.Size() == 2)
    {
        *value = ToInt(words[1]);       // TODO Здесь ноль и true возвращается в том случае, когда преобразование выполнено с ошибкой
        return true;
    }

    return false;
}


bool ConsoleParser::ExtractFloat(const String &str, float *value)
{
    Vector<String> words = str.Split(':');

    if(words.Size() == 2)
    {
        *value = ToFloat(words[1]);     // Здесь 0.0f возвращается в том случае, если преобразование выполнено с ошибкой
        return true;
    }

    return false;
}


bool ConsoleParser::BeginFrom(const String &str, const char *begin)
{
    return str.Substring(str[0] == '-' ? 1U : 0U, static_cast<uint>(strlen(begin))) == String(begin);
}


bool ConsoleParser::Run(const ParserStruct *structs, Vector<String> &words, bool showInfo)
{
    const ParserStruct *str = structs;

    if(showInfo)
    {
        uint64 length = 0;
        while(str->command)
        {
            if(strlen(str->command) > length)
            {
                length = static_cast<uint64>(strlen(str->command));
            }
            str++;
        }

        str = structs;

        while(str->command)
        {
            String message = " -" + String(str->command);
            if(str->typeParameter == Int)
            {
                message += ":XX";
            }
            else if(str->typeParameter == Float)
            {
                message += ":X.X";
            }
            while(message.Length() < length + 8)
            {
                message.Append(' ');
            }
            TheConsole->Write(message + str->help);
            str++;
        }
    }
    else
    {
        if(words.Size())
        {
            while(str->command)
            {
                if(BeginFrom(words[0], str->command))
                {
                    return (this->*str->func)(words, false);
                }
                str++;
            }
        }
    }
    return false;
}



ConsoleT::ConsoleT() :
    WindowT(TheContext)
{
    SetVisible(false);
    SetResizable(true);

    SetSize(TheGraphics->GetWidth(), 300);
    SetResizable(true);

    lineEdit = TheUIRoot->CreateChild<LineEdit>();
    lineEdit->SetStyle("LineEdit");

    AddChild(lineEdit);

    /*
    scrollBar = TheUIRoot->CreateChild<ScrollBar>();
    scrollBar->SetFixedSize(10, GetHeight() - 15);
    scrollBar->SetPosition(GetWidth() - 10, 0);
    scrollBar->SetStyleAuto();
    scrollBar->SetOrientation(O_VERTICAL);
    scrollBar->SetRange(0.0f);
    AddChild(scrollBar);
    */

    text = TheUIRoot->CreateChild<Text>();
    text->SetStyle("MenuPage");
    text->SetWordwrap(true);
    AddChild(text);

    SubscribeToEvent(lineEdit, E_TEXTFINISHED, URHO3D_HANDLER(ConsoleT, HandleFinishedText));
    SubscribeToEvent(lineEdit, E_UNHANDLEDKEY, URHO3D_HANDLER(ConsoleT, HandleUnhandledKey));
    SubscribeToEvent(text, E_CLICK, URHO3D_HANDLER(ConsoleT, HandleClick));
    SubscribeToEvent(this, E_CLICK, URHO3D_HANDLER(ConsoleT, HandleClick));
    SubscribeToEvent(this, E_RESIZED, URHO3D_HANDLER(ConsoleT, HandleResize));

    VariantMap map;
    HandleResize("", map);
}


void ConsoleT::Toggle()
{
   SetVisible(!IsVisible());
   if(IsVisible())
   {
       this->BringToFront();
       TheUI->SetFocusElement(lineEdit);
   }
}


bool ConsoleT::IsActive()
{
    return lineEdit->HasFocus();
}


void ConsoleT::HandleFinishedText(StringHash, VariantMap&)
{
    String command = lineEdit->GetText();
    if(command.Empty())
    {
        return;
    }
    history.AddString(command);

    String message;

    Write(message + "> " + command);

    parser.Execute(command);

    lineEdit->SetText("");
}


void ConsoleT::HandleUnhandledKey(StringHash, VariantMap& eventData)
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


void ConsoleT::HandleClick(StringHash, VariantMap&)
{
    lineEdit->SetFocus(true);
}


void ConsoleT::HandleResize(StringHash, VariantMap&)
{
    lineEdit->SetSize(GetWidth() - 20, 15);
    lineEdit->SetPosition(2, GetHeight() - 15);

    text->SetFixedSize(GetWidth(), GetHeight() - 20);
    text->SetPosition(2, 0);

    // Теперь ограничим количество строк
#define MAX_STRING 100
    while (text->GetNumRows() > MAX_STRING)
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


void ConsoleT::Write(const String &message)
{
    if(message[0] == '>')
    {
        text->SetText(text->GetText() + "\n");
    }

    String str;

#ifdef _WINDOWS

    SYSTEMTIME st;
    GetLocalTime(&st);
    str = GF::IntToString(st.wHour, 2) + ":" + GF::IntToString(st.wMinute, 2) + ":" + GF::IntToString(st.wSecond, 2) +
        ":" + GF::IntToString(st.wMilliseconds, 3) + " ";

#endif

    if(message[0] != '>')
    {
        str.Append("< ");
    }

    str += message + "\n";

    URHO3D_LOGERROR(message);

    //text->SetText(text->GetText() + str);

    VariantMap map;
    HandleResize("", map);
}


void ConsoleT::Clear()
{
    text->SetText("");
    text->SetPosition(2, 0);
}



History::History()
{
    SharedPtr<File> fileRead;
    fileRead = new File(TheContext);
    if (fileRead->Open(GF::GetNameFile("history.txt"), FILE_READ))
    {
        while (!fileRead->IsEof())
        {
            strings.Push(fileRead->ReadString());
        }
        fileRead->Close();
    }
    position = static_cast<int>(strings.Size());
}


History::~History()
{
    SharedPtr<File> file;
    file = new File(TheContext);
    String name = GF::GetNameFile("history.txt");
    if (file->Open(name, FILE_READ))
    {
        file->Close();
        file->Open(name, FILE_WRITE);
        while (strings.Size() > 100)
        {
            strings.Erase(0);
        }
        for (uint i = 0; i < strings.Size(); i++)
        {
            file->WriteString(strings[i]);
        }
        file->Close();
    }
}


void History::AddString(const String &string)
{
    if(strings.Contains(string))
    {
        strings.Remove(string);
    }
    strings.Push(string);
    position = static_cast<int>(strings.Size());
}


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

    return strings[static_cast<uint>(position)];
}


String History::GetNext()
{
    if(strings.Size() == 0)
    {
        return String::EMPTY;
    }

    position++;
    if(static_cast<uint>(position) > strings.Size() - 1)
    {
        position = static_cast<int>(strings.Size()) - 1;
    }

    return strings[static_cast<uint>(position)];
}

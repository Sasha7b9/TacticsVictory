#include <stdafx.h>
#include "Console.h"
#include "GlobalFunctions.h"
#include "TacticsVictory.h"
#include "GUI/Windows/WindowVariables.h"
#include "GUI/Menu/MenuRTS.h"
#include "Network/Client.h"
#include "Network/Server.h"
#include "Network/NetworkMessages.h"
#include "Network/VectorBufferRTS.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TAB "    "


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ConsoleParser::ConsoleParser(Context *context) : Object(context)
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ConsoleParser::Execute(const String &string)
{
    const ParserStruct structs[100] =
    {
        {"clear",   None,   &ConsoleParser::FuncClear,  L"очистить консоль"},
        {"client",  None,   &ConsoleParser::FuncClient, L"функции работы с клиентом"},
        {"close",   None,   &ConsoleParser::FuncClose,  L"закрыть консоль"},
        {"exit",    None,   &ConsoleParser::FuncExit,   L"выход"},
        {"server",  None,   &ConsoleParser::FuncServer, L"функции работы с сервером"},
        {"vars",    None,   &ConsoleParser::FuncVars,   L"окно переменных"}
    };

    Vector<String> words = string.ToLower().Split(' ');

    if(!ShowBriefHelp(structs, words))
    {
        if(!ShowFullHelp(structs, words))
        {
            if(!ExecuteCommand(structs, words))
            {
                gConsole->Write(L"Неизвестная команда. Для просмотра списка доступных команд наберите \"?\"");
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::ShowBriefHelp(const ParserStruct *structs, const Vector<String> &words)
{
    if(words[0] == "?")
    {
        const ParserStruct *str = structs;

        uint length = 0;
        while(str->command)
        {
            if(strlen(str->command) > length)
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

            gConsole->Write(message + str->help);
            str++;
        }

        return true;
    }
    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::ShowFullHelp(const ParserStruct *structs, Vector<String> &words)
{
    const ParserStruct *str = structs;

    if(words.Size() > 1 && words[1] == "?")
    {
        while(str->command)
        {
            if(BeginFrom(words[0], str->command))
            {
                gConsole->Write(String(str->command) + "  " + str->help);

                (this->*str->func)(words, true);

                return true;
            }
            str++;
        }
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
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
                gConsole->Write(ToString("Invalid command syntax. For more information, type \"%s -?\"", forMSG.CString()));
            }

            return true;
        }

        str++;
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::ExtractInt(String &str, int *value)
{
    Vector<String> words = str.Split(':');

    if(words.Size() == 2)
    {
        *value = ToInt(words[1]);       // TODO Здесь ноль и true возвращается в том случае, когда преобразование выполнено с ошибкой
        return true;
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::ExtractFloat(String &str, float *value)
{
    Vector<String> words = str.Split(':');

    if(words.Size() == 2)
    {
        *value = ToFloat(words[1]);     // Здесь 0.0f возвращается в том случае, если преобразование выполнено с ошибкой
        return true;
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::BeginFrom(const String &str, const char *begin)
{
    return str.Substring(str[0] == '-' ? 1U : 0U, (uint)strlen(begin)) == String(begin);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncExit(Vector<String> &, bool showInfo)
{
    if(!showInfo)
    {
        gClient->Disconnect();
        gServer->Disconnect();
        gEngine->Exit();
    }
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncClear(Vector<String> &, bool showInfo)
{
    if(!showInfo)
    {
        gConsole->Clear();
    }
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncClose(Vector<String> &, bool showInfo)
{
    if(!showInfo)
    {
        gConsole->Toggle();
    }
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncServerStart(Vector<String> &words, bool)
{
    int port = 0;

    if(!ExtractInt(words[0], &port))
    {
        return false;
    }

    static Vector<String> arguments;
    arguments.Push(ToString("-port:%d", port));
    gFileSystem->SystemRunAsync(GetFileName("TVserver.exe"), arguments);
    serverRunning = true;
    SubscribeToEvent(E_ASYNCLOADFINISHED, URHO3D_HANDLER(ConsoleParser, HandleAsyncExecFinished));

    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncServerStop(Vector<String> &,bool)
{
    if(serverRunning)
    {
        gClient->Send(MSG_DELETE_SERVER, VectorBufferRTS());
    }
    else
    {
        gConsole->Write("Forbidden");
    }
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncServerLatency(Vector<String> &words, bool)
{
    int latency = 0;
    
    if(ExtractInt(words[0], &latency))
    {
        gClient->Send(MSG_SET_NETWORK_LATENCY, VectorBufferRTS(latency));
        return true;
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncServerPacketLoss(Vector<String> &words, bool)
{
    float loss = 0.0f;

    if(ExtractFloat(words[0], &loss))
    {
        gClient->Send(MSG_SET_NETWORK_LOSS, VectorBufferRTS(loss));
        return true;
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncServer(Vector<String> &words, bool showInfo)
{
    const ParserStruct structs[100] =
    {
        {"start",       Int,    &ConsoleParser::FuncServerStart,        L"cоздать сервер на порт XX"},
        {"stop",        None,   &ConsoleParser::FuncServerStop,         L"остановить сервер"},
        {"latency",     Int,    &ConsoleParser::FuncServerLatency,      L"эмулировать задержку сети длительностью XX миллисекунд"},
        {"packetloss",  Float,  &ConsoleParser::FuncServerPacketLoss,   L"эмулировать потерю X.X пакетров"}
    };

    return Run(structs, words, showInfo);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncVarsOpen(Vector<String> &, bool)
{
    gWindowVars->SetVisible(true);
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncVarsClose(Vector<String> &, bool)
{
    gWindowVars->SetVisible(false);
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncVars(Vector<String> &words, bool showInfo)
{
    const ParserStruct structs[100] =
    {
        {"open",    None,   &ConsoleParser::FuncVarsOpen,   L"открыть окно переменных"},
        {"close",   None,   &ConsoleParser::FuncVarsClose,  L"закрыть окно переменных"}
    };

    if(words.Size() || showInfo)
    {
        return Run(structs, words, showInfo);
    }
    else
    {
        gWindowVars->SetVisible(!gWindowVars->IsVisible());
        return true;
    }

    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::Run(const ParserStruct *structs, Vector<String> &words, bool showInfo)
{
    const ParserStruct *str = structs;

    if(showInfo)
    {
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
            gConsole->Write(message + str->help);
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ConsoleParser::HandleAsyncExecFinished(StringHash, VariantMap& data)
{
    using namespace AsyncExecFinished;

    int exitCode = data[P_EXITCODE].GetInt();

    if(exitCode)
    {
        gConsole->Write(L"Сервер завершил работу с кодом ошибки");
    }
    else
    {
        gConsole->Write(L"Сервер завершил работу");
    }

    UnsubscribeFromEvent(E_ASYNCLOADFINISHED);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void OnServerConnected()
{
    gClient->Send(MSG_REQUEST_LANDSCAPE, VectorBufferRTS());
    gConsole->Write(L"Запрашиваю ландшафт");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncClientStart(Vector<String> &words, bool)
{
    String address = SERVER_ADDRESS;
    uint16 port = SERVER_PORT;
    if(!GetAddressPort(words, address, port))
    {
        return false;
    }

    if(gClient->IsConnected())
    {
        gConsole->Write("Command forbidden. The client already running");
    }
    else
    {
        gMenu->Hide();
        gClient->StartConnecting(SERVER_ADDRESS, SERVER_PORT, OnServerConnected);
        gConsole->Write(L"Соединяюсь с удалённым сервером...");
    }

    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncClientStop(Vector<String> &, bool)
{
    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncClient(Vector<String> &words, bool showInfo)
{
    const ParserStruct structs[100] =
    {
        {"start",   None,   &ConsoleParser::FuncClientStart,    L"запуск клиента. Формат команды - client -start -address:XX.XX.XX.XX -port:XX"},
        {"stop",    None,   &ConsoleParser::FuncClientStop,     L"останов клиента"}
    };

    return Run(structs, words, showInfo);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ConsoleRTS::ConsoleRTS(Context *context) :
    WindowRTS(context)
{
    SetVisible(false);
    SetResizable(true);

    SetSize(gGraphics->GetWidth(), 300);
    SetResizable(true);

    lineEdit = gUIRoot->CreateChild<LineEdit>();
    lineEdit->SetStyle("LineEdit");

    AddChild(lineEdit);

    /*
    scrollBar = gUIRoot->CreateChild<ScrollBar>();
    scrollBar->SetFixedSize(10, GetHeight() - 15);
    scrollBar->SetPosition(GetWidth() - 10, 0);
    scrollBar->SetStyleAuto();
    scrollBar->SetOrientation(O_VERTICAL);
    scrollBar->SetRange(0.0f);
    AddChild(scrollBar);
    */

    text = gUIRoot->CreateChild<Text>();
    text->SetStyle("WindowMenu");
    text->SetWordwrap(true);
    AddChild(text);

    SubscribeToEvent(lineEdit, E_TEXTFINISHED, URHO3D_HANDLER(ConsoleRTS, HandleFinishedText));
    SubscribeToEvent(lineEdit, E_UNHANDLEDKEY, URHO3D_HANDLER(ConsoleRTS, HandleUnhandledKey));
    SubscribeToEvent(text, E_CLICK, URHO3D_HANDLER(ConsoleRTS, HandleClick));
    SubscribeToEvent(this, E_CLICK, URHO3D_HANDLER(ConsoleRTS, HandleClick));
    SubscribeToEvent(this, E_RESIZED, URHO3D_HANDLER(ConsoleRTS, HandleResize));

    VariantMap map;
    HandleResize("", map);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ConsoleRTS::Toggle()
{
   SetVisible(!IsVisible());
   if(IsVisible())
   {
       this->BringToFront();
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

    Write(message + "> " + command);

    parser.Execute(command);

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
void ConsoleRTS::HandleClick(StringHash, VariantMap&)
{
    lineEdit->SetFocus(true);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ConsoleRTS::HandleResize(StringHash, VariantMap&)
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef CLIENT
void ConsoleRTS::Write(const String &message)
{
    if(message[0] == '>')
    {
        text->SetText(text->GetText() + "\n");
    }

    String str;

#ifdef _WINDOWS

    SYSTEMTIME st;
    GetLocalTime(&st);
    str = IntToString(st.wHour, 2) + ":" + IntToString(st.wMinute, 2) + ":" + IntToString(st.wSecond, 2) + ":" + IntToString(st.wMilliseconds, 3) + " ";

#endif

    if(message[0] != '>')
    {
        str.Append("< ");
    }

    str += message + "\n";

    text->SetText(text->GetText() + str);

    VariantMap map;
    HandleResize("", map);
}
#else
void ConsoleRTS::Write(const String &) {}
#endif


//----------------------------------------------------------------------------------------------------------------------------------------------------
void ConsoleRTS::Clear()
{
    text->SetText("");
    text->SetPosition(2, 0);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
History::History()
{
    SharedPtr<File> fileRead;
    fileRead = new File(gContext);
    if (fileRead->Open(GetNameFile("history.txt"), FILE_READ))
    {
        while (!fileRead->IsEof())
        {
            strings.Push(fileRead->ReadString());
        }
        fileRead->Close();
    }
    position = (int)strings.Size();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
History::~History()
{
    SharedPtr<File> file;
    file = new File(gContext);
    String name = GetNameFile("history.txt");
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
